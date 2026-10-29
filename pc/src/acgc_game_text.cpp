#include "acgc/game_text.hpp"
#include <array>
#include <cstring>

namespace acgc::text {
namespace {
constexpr int kGameCharTilde = 42;
constexpr int kGameCharForwardSlash = 174;
constexpr int kGameCharPlus = 180;
constexpr int kGameCharSemicolon = 208;
constexpr int kGameCharHashtag = 209;
constexpr int kGameCharBackslash = 222;
} // namespace

int decode(std::string_view text, std::size_t& consumed) {
    consumed = text.empty() ? 0 : 1;
    if (text.empty()) {
        return -1;
    }
    const unsigned char lead = static_cast<unsigned char>(text[0]);

    if (lead < 0x80) {
        static constexpr std::array<int, 128> ascii_map = {
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            ' ',
            '!',
            '"',
            kGameCharHashtag,
            -1,
            '%',
            '&',
            0x27,
            '(',
            ')',
            -1,
            kGameCharPlus,
            ',',
            '-',
            '.',
            kGameCharForwardSlash,
            '0',
            '1',
            '2',
            '3',
            '4',
            '5',
            '6',
            '7',
            '8',
            '9',
            ':',
            kGameCharSemicolon,
            '<',
            '=',
            '>',
            '?',
            '@',
            'A',
            'B',
            'C',
            'D',
            'E',
            'F',
            'G',
            'H',
            'I',
            'J',
            'K',
            'L',
            'M',
            'N',
            'O',
            'P',
            'Q',
            'R',
            'S',
            'T',
            'U',
            'V',
            'W',
            'X',
            'Y',
            'Z',
            -1,
            kGameCharBackslash,
            -1,
            -1,
            '_',
            -1,
            'a',
            'b',
            'c',
            'd',
            'e',
            'f',
            'g',
            'h',
            'i',
            'j',
            'k',
            'l',
            'm',
            'n',
            'o',
            'p',
            'q',
            'r',
            's',
            't',
            'u',
            'v',
            'w',
            'x',
            'y',
            'z',
            -1,
            -1,
            -1,
            kGameCharTilde,
            -1,
        };
        return ascii_map[lead];
    }

    if (lead < 0xC2 || lead > 0xDF || text.size() < 2) {
        return -1;
    }

    const unsigned char continuation = static_cast<unsigned char>(text[1]);
    if ((continuation & 0xC0) != 0x80) {
        return -1;
    }
    consumed = 2;
    const int codepoint = ((lead & 0x1F) << 6) | (continuation & 0x3F);

    if (codepoint == 0xA1) {
        return 0;
    }
    if (codepoint == 0xBF) {
        return 1;
    }
    if (codepoint >= 0xC0 && codepoint <= 0xDF) {
        // Animal Crossing font codes corresponding to U+00C0 through U+00DF.
        static constexpr std::array<int, 32> uppercase = {
            3,  4,  5,  6,  2,  7,  162, 8,  9,  10, 11, 12, 13, 14,  15, 16,
            17, 18, 19, 20, 21, 22, 23,  -1, 24, 25, 26, 27, 28, 150, 30, 29,
        };
        return uppercase[codepoint - 0xC0];
    }
    if (codepoint >= 0xE0 && codepoint <= 0xFF) {
        // Animal Crossing font codes corresponding to U+00E0 through U+00FF.
        static constexpr std::array<int, 32> lowercase = {
            31,  35,  36,  91,  93,  94,  163, 96, 123, 124, 125, 126, 129, 130, 131, 132,
            134, 135, 136, 137, 138, 139, 140, -1, 141, 142, 143, 145, 146, 147, 149, 148,
        };
        return lowercase[codepoint - 0xE0];
    }

    return -1;
}

std::string_view encode(uint8_t code) {
    static const auto table = [] {
        std::array<std::array<char, 3>, 256> result{};
        for (int codepoint = 0xFF; codepoint >= 0x20; --codepoint) {
            if (codepoint > 0x7E && codepoint < 0xA1) {
                continue;
            }
            char encoded[3] = {};
            if (codepoint < 0x80) {
                encoded[0] = static_cast<char>(codepoint);
            } else {
                encoded[0] = static_cast<char>(0xC0 | (codepoint >> 6));
                encoded[1] = static_cast<char>(0x80 | (codepoint & 0x3F));
            }
            std::size_t consumed = 0;
            const int game_code = decode(encoded, consumed);
            if (game_code >= 0 && game_code < 256) {
                std::memcpy(result[game_code].data(), encoded, sizeof(encoded));
            }
        }
        return result;
    }();
    return table[code].data();
}

} // namespace acgc::text
