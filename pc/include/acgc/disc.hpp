#pragma once

#include "acgc/settings.hpp"

#include <borealis/disc.hpp>

#include <cstdint>
#include <string>
#include <string_view>

namespace acgc::disc {

enum class ValidationError : std::uint8_t {
    Unknown = 0,
    IOError,
    InvalidImage,
    WrongGame,
    WrongVersion,
    Canceled,
    HashMismatch,
    Success,
};

using VerificationStatus = borealis::disc::Progress;

struct DiscInfo {
    std::string gameId;
    std::string title;
    std::uint8_t discNumber = 0;
    std::uint8_t revision = 0;
};

ValidationError inspect(std::string_view path, DiscInfo& info);
ValidationError verify(std::string_view path, VerificationStatus& status, DiscInfo& info);
void log_verification_state(std::string_view path, DiscVerificationState state);

} // namespace acgc::disc
