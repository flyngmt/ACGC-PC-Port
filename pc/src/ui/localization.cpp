#include "acgc/ui/localization.hpp"

#include "acgc/ui/ui.hpp"

#include <SDL3/SDL_locale.h>
#include <SDL3/SDL_stdinc.h>
#include <RmlUi/Core.h>
#include <borealis/io.hpp>
#include <borealis/log.hpp>
#include <nlohmann/json.hpp>

#include <cctype>
#include <functional>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace acgc::ui::localization {
namespace {

constexpr borealis::Log Log{"acgc::ui::localization"};
constexpr bool kDetectPreferredLocale = false;

using Catalog = std::map<std::string, Rml::String, std::less<>>;

Catalog sEnglish;
Catalog sLocalized;
std::set<std::string, std::less<>> sMissingKeys;

bool valid_locale_part(std::string_view value)
{
    if (value.empty()) {
        return false;
    }
    for (const unsigned char c : value) {
        if (!std::isalnum(c) && c != '-') {
            return false;
        }
    }
    return true;
}

bool load_catalog(const std::filesystem::path& path, Catalog& catalog)
{
    const std::string pathString = borealis::io::fs_path_to_string(path);
    Rml::FileInterface* fileInterface = Rml::GetFileInterface();
    Rml::String source;
    if (fileInterface == nullptr || !fileInterface->LoadFile(pathString, source)) {
        return false;
    }

    try {
        const nlohmann::json root = nlohmann::json::parse(source);
        if (!root.is_object()) {
            throw std::runtime_error("catalog root must be an object");
        }
        for (const auto& [key, value] : root.items()) {
            if (value.is_string()) {
                catalog.insert_or_assign(key, value.get<std::string>());
            } else {
                Log.warn("Ignoring non-string translation '{}' in '{}'", key, pathString);
            }
        }
    } catch (const std::exception& error) {
        Log.warn("Could not parse translation catalog '{}': {}", pathString, error.what());
        return false;
    }
    return true;
}

std::vector<std::string> preferred_catalog_names()
{
    std::vector<std::string> names;
    int count = 0;
    SDL_Locale** locales = SDL_GetPreferredLocales(&count);
    for (int i = 0; locales != nullptr && i < count; ++i) {
        const SDL_Locale* locale = locales[i];
        if (locale == nullptr || locale->language == nullptr ||
            !valid_locale_part(locale->language)) {
            continue;
        }

        const std::string language = locale->language;
        if (locale->country != nullptr && valid_locale_part(locale->country)) {
            names.push_back(language + "_" + locale->country);
        }
        names.push_back(language);
    }
    SDL_free(locales);
    return names;
}

} // namespace

void load() noexcept
{
    sEnglish.clear();
    sLocalized.clear();
    sMissingKeys.clear();

    const auto directory = resource_path("lang");
    const auto englishPath = directory / "en.json";
    if (!load_catalog(englishPath, sEnglish)) {
        Log.warn("English UI catalog '{}' is unavailable; translation keys will be shown",
                 borealis::io::fs_path_to_string(englishPath));
        return;
    }
    if (!kDetectPreferredLocale) {
        return;
    }
    for (const std::string& name : preferred_catalog_names()) {
        if (name == "en" || name.starts_with("en_")) {
            break;
        }
        const auto path = directory / (name + ".json");
        if (!load_catalog(path, sLocalized)) {
            continue;
        }
        Log.info("Loaded UI translations from '{}'",
                 borealis::io::fs_path_to_string(path));
        break;
    }
}

void shutdown() noexcept
{
    sLocalized.clear();
    sEnglish.clear();
    sMissingKeys.clear();
}

Rml::String get(std::string_view key) noexcept
{
    if (const auto found = sLocalized.find(key); found != sLocalized.end()) {
        return found->second;
    }
    if (const auto found = sEnglish.find(key); found != sEnglish.end()) {
        return found->second;
    }
    if (sMissingKeys.emplace(key).second) {
        Log.warn("Missing UI translation '{}'", key);
    }
    return Rml::String(key);
}

} // namespace acgc::ui::localization
