#ifndef COLORS_HPP
#define COLORS_HPP

struct Color {
  float r, g, b;
  Color(float _r, float _g, float _b) {
    r = _r;
    g = _g;
    b = _b;
  }
  Color(const Color &c) {
    r = c.r;
    g = c.g;
    b = c.b;
  }
};
#endif