#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace hg::font {

constexpr int kGlyphWidth = 5;
constexpr int kGlyphHeight = 7;
// Advance and line pitch at scale 1 (glyph plus one pixel of spacing).
constexpr int kCellWidth = 6;
constexpr int kCellHeight = 9;

// Row-major glyph pixels: kGlyphWidth * kGlyphHeight chars, '#' = on.
const char* glyph(char c);
// Render one Unicode codepoint into caller-owned row-major pixels. Vietnamese
// Latin letters keep their base letter and a compact tone/diacritic mark.
bool glyph(uint32_t codepoint, char* out);
uint32_t next_utf8(std::string_view text, size_t& offset);
size_t utf8_length(std::string_view text);

}  // namespace hg::font
