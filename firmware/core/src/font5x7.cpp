// 5x7 bitmap font for printable ASCII (0x20..0x7E), drawn as ASCII art so the
// glyphs are reviewable in a diff. '#' is an "on" pixel. Each entry is seven
// 5-character rows concatenated by the compiler.
#include "hg/font.hpp"

#include <cstring>

namespace hg::font {
namespace {

const char* const kGlyphs[95] = {
    // ' '
    "....." "....." "....." "....." "....." "....." ".....",
    // '!'
    "..#.." "..#.." "..#.." "..#.." "..#.." "....." "..#..",
    // '"'
    ".#.#." ".#.#." ".#.#." "....." "....." "....." ".....",
    // '#'
    ".#.#." ".#.#." "#####" ".#.#." "#####" ".#.#." ".#.#.",
    // '$'
    "..#.." ".####" "#.#.." ".###." "..#.#" "####." "..#..",
    // '%'
    "##..." "##..#" "...#." "..#.." ".#..." "#..##" "...##",
    // '&'
    ".##.." "#..#." "#.#.." ".#..." "#.#.#" "#..#." ".##.#",
    // '\''
    "..#.." "..#.." ".#..." "....." "....." "....." ".....",
    // '('
    "...#." "..#.." ".#..." ".#..." ".#..." "..#.." "...#.",
    // ')'
    ".#..." "..#.." "...#." "...#." "...#." "..#.." ".#...",
    // '*'
    "....." "..#.." "#.#.#" ".###." "#.#.#" "..#.." ".....",
    // '+'
    "....." "..#.." "..#.." "#####" "..#.." "..#.." ".....",
    // ','
    "....." "....." "....." "....." ".##.." "..#.." ".#...",
    // '-'
    "....." "....." "....." "#####" "....." "....." ".....",
    // '.'
    "....." "....." "....." "....." "....." ".##.." ".##..",
    // '/'
    "....." "....#" "...#." "..#.." ".#..." "#...." ".....",
    // '0'
    ".###." "#...#" "#..##" "#.#.#" "##..#" "#...#" ".###.",
    // '1'
    "..#.." ".##.." "..#.." "..#.." "..#.." "..#.." ".###.",
    // '2'
    ".###." "#...#" "....#" "...#." "..#.." ".#..." "#####",
    // '3'
    "#####" "...#." "..#.." "...#." "....#" "#...#" ".###.",
    // '4'
    "...#." "..##." ".#.#." "#..#." "#####" "...#." "...#.",
    // '5'
    "#####" "#...." "####." "....#" "....#" "#...#" ".###.",
    // '6'
    "..##." ".#..." "#...." "####." "#...#" "#...#" ".###.",
    // '7'
    "#####" "....#" "...#." "..#.." ".#..." ".#..." ".#...",
    // '8'
    ".###." "#...#" "#...#" ".###." "#...#" "#...#" ".###.",
    // '9'
    ".###." "#...#" "#...#" ".####" "....#" "...#." ".##..",
    // ':'
    "....." ".##.." ".##.." "....." ".##.." ".##.." ".....",
    // ';'
    "....." ".##.." ".##.." "....." ".##.." "..#.." ".#...",
    // '<'
    "...#." "..#.." ".#..." "#...." ".#..." "..#.." "...#.",
    // '='
    "....." "....." "#####" "....." "#####" "....." ".....",
    // '>'
    ".#..." "..#.." "...#." "....#" "...#." "..#.." ".#...",
    // '?'
    ".###." "#...#" "....#" "...#." "..#.." "....." "..#..",
    // '@'
    ".###." "#...#" "....#" ".##.#" "#.#.#" "#.#.#" ".###.",
    // 'A'
    ".###." "#...#" "#...#" "#####" "#...#" "#...#" "#...#",
    // 'B'
    "####." "#...#" "#...#" "####." "#...#" "#...#" "####.",
    // 'C'
    ".###." "#...#" "#...." "#...." "#...." "#...#" ".###.",
    // 'D'
    "###.." "#..#." "#...#" "#...#" "#...#" "#..#." "###..",
    // 'E'
    "#####" "#...." "#...." "####." "#...." "#...." "#####",
    // 'F'
    "#####" "#...." "#...." "####." "#...." "#...." "#....",
    // 'G'
    ".###." "#...#" "#...." "#.###" "#...#" "#...#" ".####",
    // 'H'
    "#...#" "#...#" "#...#" "#####" "#...#" "#...#" "#...#",
    // 'I'
    ".###." "..#.." "..#.." "..#.." "..#.." "..#.." ".###.",
    // 'J'
    "..###" "...#." "...#." "...#." "...#." "#..#." ".##..",
    // 'K'
    "#...#" "#..#." "#.#.." "##..." "#.#.." "#..#." "#...#",
    // 'L'
    "#...." "#...." "#...." "#...." "#...." "#...." "#####",
    // 'M'
    "#...#" "##.##" "#.#.#" "#.#.#" "#...#" "#...#" "#...#",
    // 'N'
    "#...#" "#...#" "##..#" "#.#.#" "#..##" "#...#" "#...#",
    // 'O'
    ".###." "#...#" "#...#" "#...#" "#...#" "#...#" ".###.",
    // 'P'
    "####." "#...#" "#...#" "####." "#...." "#...." "#....",
    // 'Q'
    ".###." "#...#" "#...#" "#...#" "#.#.#" "#..#." ".##.#",
    // 'R'
    "####." "#...#" "#...#" "####." "#.#.." "#..#." "#...#",
    // 'S'
    ".####" "#...." "#...." ".###." "....#" "....#" "####.",
    // 'T'
    "#####" "..#.." "..#.." "..#.." "..#.." "..#.." "..#..",
    // 'U'
    "#...#" "#...#" "#...#" "#...#" "#...#" "#...#" ".###.",
    // 'V'
    "#...#" "#...#" "#...#" "#...#" "#...#" ".#.#." "..#..",
    // 'W'
    "#...#" "#...#" "#...#" "#.#.#" "#.#.#" "#.#.#" ".#.#.",
    // 'X'
    "#...#" "#...#" ".#.#." "..#.." ".#.#." "#...#" "#...#",
    // 'Y'
    "#...#" "#...#" "#...#" ".#.#." "..#.." "..#.." "..#..",
    // 'Z'
    "#####" "....#" "...#." "..#.." ".#..." "#...." "#####",
    // '['
    ".###." ".#..." ".#..." ".#..." ".#..." ".#..." ".###.",
    // '\\'
    "....." "#...." ".#..." "..#.." "...#." "....#" ".....",
    // ']'
    ".###." "...#." "...#." "...#." "...#." "...#." ".###.",
    // '^'
    "..#.." ".#.#." "#...#" "....." "....." "....." ".....",
    // '_'
    "....." "....." "....." "....." "....." "....." "#####",
    // '`'
    ".#..." "..#.." "...#." "....." "....." "....." ".....",
    // 'a'
    "....." "....." ".###." "....#" ".####" "#...#" ".####",
    // 'b'
    "#...." "#...." "#.##." "##..#" "#...#" "#...#" "####.",
    // 'c'
    "....." "....." ".###." "#...." "#...." "#...#" ".###.",
    // 'd'
    "....#" "....#" ".##.#" "#..##" "#...#" "#...#" ".####",
    // 'e'
    "....." "....." ".###." "#...#" "#####" "#...." ".###.",
    // 'f'
    "..##." ".#..#" ".#..." "###.." ".#..." ".#..." ".#...",
    // 'g'
    "....." ".####" "#...#" "#...#" ".####" "....#" ".###.",
    // 'h'
    "#...." "#...." "#.##." "##..#" "#...#" "#...#" "#...#",
    // 'i'
    "..#.." "....." ".##.." "..#.." "..#.." "..#.." ".###.",
    // 'j'
    "...#." "....." "..##." "...#." "...#." "#..#." ".##..",
    // 'k'
    "#...." "#...." "#..#." "#.#.." "##..." "#.#.." "#..#.",
    // 'l'
    ".##.." "..#.." "..#.." "..#.." "..#.." "..#.." ".###.",
    // 'm'
    "....." "....." "##.#." "#.#.#" "#.#.#" "#...#" "#...#",
    // 'n'
    "....." "....." "#.##." "##..#" "#...#" "#...#" "#...#",
    // 'o'
    "....." "....." ".###." "#...#" "#...#" "#...#" ".###.",
    // 'p'
    "....." "....." "####." "#...#" "####." "#...." "#....",
    // 'q'
    "....." "....." ".####" "#...#" ".####" "....#" "....#",
    // 'r'
    "....." "....." "#.##." "##..#" "#...." "#...." "#....",
    // 's'
    "....." "....." ".####" "#...." ".###." "....#" "####.",
    // 't'
    ".#..." ".#..." "###.." ".#..." ".#..." ".#..#" "..##.",
    // 'u'
    "....." "....." "#...#" "#...#" "#...#" "#..##" ".##.#",
    // 'v'
    "....." "....." "#...#" "#...#" "#...#" ".#.#." "..#..",
    // 'w'
    "....." "....." "#...#" "#...#" "#.#.#" "#.#.#" ".#.#.",
    // 'x'
    "....." "....." "#...#" ".#.#." "..#.." ".#.#." "#...#",
    // 'y'
    "....." "....." "#...#" "#...#" ".####" "....#" ".###.",
    // 'z'
    "....." "....." "#####" "...#." "..#.." ".#..." "#####",
    // '{'
    "...#." "..#.." "..#.." ".#..." "..#.." "..#.." "...#.",
    // '|'
    "..#.." "..#.." "..#.." "..#.." "..#.." "..#.." "..#..",
    // '}'
    ".#..." "..#.." "..#.." "...#." "..#.." "..#.." ".#...",
    // '~'
    "....." "....." ".#..." "#.#.#" "...#." "....." ".....",
};

}  // namespace

const char* glyph(char c) {
  unsigned char u = static_cast<unsigned char>(c);
  if (u < 0x20 || u > 0x7E) u = '?';
  return kGlyphs[u - 0x20];
}

namespace {

enum class Mark : uint8_t { None, Grave, Acute, Hook, Tilde, Dot, Circumflex, Breve, Horn };

struct VietnameseGlyph {
  char base;
  Mark shape;
  Mark tone;
};

bool find_in(const uint32_t cp, const uint32_t* cps, size_t n, char base, Mark shape,
             VietnameseGlyph& out) {
  for (size_t i = 0; i < n; ++i) {
    if (cps[i] == cp) {
      out = {base, shape, static_cast<Mark>(i == 0 ? Mark::Grave : i == 1 ? Mark::Acute :
                                                   i == 2 ? Mark::Hook : i == 3 ? Mark::Tilde : Mark::Dot)};
      return true;
    }
  }
  return false;
}

bool vietnamese(uint32_t cp, VietnameseGlyph& out) {
  static constexpr uint32_t A[] = {0x00C0, 0x00C1, 0x1EA2, 0x00C3, 0x1EA0,
                                   0x1EA6, 0x1EA4, 0x1EA8, 0x1EAA, 0x1EAC,
                                   0x1EB0, 0x1EAE, 0x1EB2, 0x1EB4, 0x1EB6};
  static constexpr uint32_t a[] = {0x00E0, 0x00E1, 0x1EA3, 0x00E3, 0x1EA1,
                                   0x1EA7, 0x1EA5, 0x1EA9, 0x1EAB, 0x1EAD,
                                   0x1EB1, 0x1EAF, 0x1EB3, 0x1EB5, 0x1EB7};
  static constexpr uint32_t E[] = {0x00C8, 0x00C9, 0x1EBA, 0x1EBC, 0x1EB8,
                                   0x1EC0, 0x1EBE, 0x1EC2, 0x1EC4, 0x1EC6};
  static constexpr uint32_t e[] = {0x00E8, 0x00E9, 0x1EBB, 0x1EBD, 0x1EB9,
                                   0x1EC1, 0x1EBF, 0x1EC3, 0x1EC5, 0x1EC7};
  static constexpr uint32_t I[] = {0x00CC, 0x00CD, 0x1EC8, 0x0128, 0x1ECA};
  static constexpr uint32_t i[] = {0x00EC, 0x00ED, 0x1EC9, 0x0129, 0x1ECB};
  static constexpr uint32_t O[] = {0x00D2, 0x00D3, 0x1ECE, 0x00D5, 0x1ECC,
                                   0x1ED2, 0x1ED0, 0x1ED4, 0x1ED6, 0x1ED8,
                                   0x1EDA, 0x1ED8, 0x1EDC, 0x1EDE, 0x1EE0};
  static constexpr uint32_t o[] = {0x00F2, 0x00F3, 0x1ECF, 0x00F5, 0x1ECD,
                                   0x1ED3, 0x1ED1, 0x1ED5, 0x1ED7, 0x1ED9,
                                   0x1EDB, 0x1ED9, 0x1EDD, 0x1EDF, 0x1EE1};
  static constexpr uint32_t U[] = {0x00D9, 0x00DA, 0x1EE6, 0x0168, 0x1EE4,
                                   0x1EEA, 0x1EE8, 0x1EEC, 0x1EEE, 0x1EF0};
  static constexpr uint32_t u[] = {0x00F9, 0x00FA, 0x1EE7, 0x0169, 0x1EE5,
                                   0x1EEB, 0x1EE9, 0x1EED, 0x1EEF, 0x1EF1};
  static constexpr uint32_t Y[] = {0x1EF2, 0x00DD, 0x1EF6, 0x1EF8, 0x1EF4};
  static constexpr uint32_t y[] = {0x1EF3, 0x00FD, 0x1EF7, 0x1EF9, 0x1EF5};
  if (cp == 0x0110) { out = {'D', Mark::None, Mark::Horn}; return true; }
  if (cp == 0x0111) { out = {'d', Mark::None, Mark::Horn}; return true; }
  if (find_in(cp, A, 5, 'A', Mark::None, out) || find_in(cp, a, 5, 'a', Mark::None, out) ||
      find_in(cp, E, 5, 'E', Mark::None, out) || find_in(cp, e, 5, 'e', Mark::None, out) ||
      find_in(cp, I, 5, 'I', Mark::None, out) || find_in(cp, i, 5, 'i', Mark::None, out) ||
      find_in(cp, O, 5, 'O', Mark::None, out) || find_in(cp, o, 5, 'o', Mark::None, out) ||
      find_in(cp, U, 5, 'U', Mark::None, out) || find_in(cp, u, 5, 'u', Mark::None, out) ||
      find_in(cp, Y, 5, 'Y', Mark::None, out) || find_in(cp, y, 5, 'y', Mark::None, out)) return true;
  if (find_in(cp, A + 5, 5, 'A', Mark::Circumflex, out) || find_in(cp, a + 5, 5, 'a', Mark::Circumflex, out) ||
      find_in(cp, E + 5, 5, 'E', Mark::Circumflex, out) || find_in(cp, e + 5, 5, 'e', Mark::Circumflex, out) ||
      find_in(cp, O + 5, 5, 'O', Mark::Circumflex, out) || find_in(cp, o + 5, 5, 'o', Mark::Circumflex, out) ||
      find_in(cp, U + 5, 5, 'U', Mark::Horn, out) || find_in(cp, u + 5, 5, 'u', Mark::Horn, out)) return true;
  if (find_in(cp, A + 10, 5, 'A', Mark::Breve, out) || find_in(cp, a + 10, 5, 'a', Mark::Breve, out) ||
      find_in(cp, O + 10, 5, 'O', Mark::Horn, out) || find_in(cp, o + 10, 5, 'o', Mark::Horn, out)) return true;
  return false;
}

void mark(char* out, Mark m) {
  if (m == Mark::Grave) out[1] = '#';
  else if (m == Mark::Acute) out[3] = '#';
  else if (m == Mark::Hook) out[2] = '#';
  else if (m == Mark::Tilde) out[0] = out[4] = '#';
  else if (m == Mark::Dot) out[6 * kGlyphWidth + 2] = '#';
  else if (m == Mark::Circumflex) { out[2] = '#'; out[kGlyphWidth + 1] = out[kGlyphWidth + 3] = '#'; }
  else if (m == Mark::Breve) { out[1] = out[3] = '#'; }
  else if (m == Mark::Horn) out[4] = '#';
}

}  // namespace

uint32_t next_utf8(std::string_view text, size_t& offset) {
  if (offset >= text.size()) return 0;
  const auto b = static_cast<unsigned char>(text[offset++]);
  if (b < 0x80) return b;
  if ((b & 0xE0) == 0xC0 && offset < text.size()) return ((b & 0x1F) << 6) | (static_cast<unsigned char>(text[offset++]) & 0x3F);
  if ((b & 0xF0) == 0xE0 && offset + 1 < text.size()) {
    uint32_t cp = (b & 0x0F) << 12;
    cp |= (static_cast<unsigned char>(text[offset++]) & 0x3F) << 6;
    return cp | (static_cast<unsigned char>(text[offset++]) & 0x3F);
  }
  if ((b & 0xF8) == 0xF0 && offset + 2 < text.size()) {
    uint32_t cp = (b & 0x07) << 18;
    cp |= (static_cast<unsigned char>(text[offset++]) & 0x3F) << 12;
    cp |= (static_cast<unsigned char>(text[offset++]) & 0x3F) << 6;
    return cp | (static_cast<unsigned char>(text[offset++]) & 0x3F);
  }
  return '?';
}

size_t utf8_length(std::string_view text) {
  size_t n = 0, offset = 0;
  while (offset < text.size()) { next_utf8(text, offset); ++n; }
  return n;
}

bool glyph(uint32_t cp, char* out) {
  if (!out) return false;
  const char* base = "?";
  VietnameseGlyph v{};
  if (vietnamese(cp, v)) {
    std::memcpy(out, glyph(v.base), kGlyphWidth * kGlyphHeight);
    mark(out, v.shape);
    mark(out, v.tone);
    return true;
  }
  if (cp < 0x80) base = glyph(static_cast<char>(cp));
  else base = glyph('?');
  std::memcpy(out, base, kGlyphWidth * kGlyphHeight);
  return cp < 0x80;
}

}  // namespace hg::font
