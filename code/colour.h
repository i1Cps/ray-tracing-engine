// Colour is a class to store and maniplulate an rgba colour.

#pragma once

class Colour {
 public:
  float r;
  float g;
  float b;
  float a;

  // Default constructor: Initializes a black color with full opacity.
  Colour() {
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
    a = 1.0f;
  }

  // Constructor with RGB values: Initializes a color with specified RGB values
  // and full opacity.
  Colour(float p_r, float p_g, float p_b) {
    r = p_r;
    g = p_g;
    b = p_b;
    a = 1.0;
  }

  // Constructor with RGBA values: Initializes a color with specified RGBA
  // values.
  Colour(float pr, float pg, float pb, float pa) {
    r = pr;
    g = pg;
    b = pb;
    a = pa;
  }

  // Scales the color by another color component-wise.
  void scale(Colour& scaling) {
    r *= scaling.r;
    g *= scaling.g;
    b *= scaling.b;
    a *= scaling.a;
  }
  // Adds another color component-wise.
  void add(Colour& adjust) {
    r += adjust.r;
    g += adjust.g;
    b += adjust.b;
  }

  // Multiplies the color by another color component-wise.
  Colour operator*(Colour other) {
    Colour result;
    result.r = r * other.r;
    result.g = g * other.g;
    result.b = b * other.b;
    result.a = a * other.a;
    return result;
  }

  // Adds another color component-wise.
  Colour operator+(Colour& other) {
    Colour result;
    result.r = r + other.r;
    result.g = g + other.g;
    result.b = b + other.b;
    result.a = a + other.a;
    return result;
  }

  // Adds another color component-wise.
  Colour operator+(Colour other) {
    Colour result;
    result.r = r + other.r;
    result.g = g + other.g;
    result.b = b + other.b;
    result.a = a + other.a;
    return result;
  }

  // Multiplies the color by a scalar value.
  Colour operator*(float rhs) {
    Colour result;
    result.r = r * rhs;
    result.g = g * rhs;
    result.b = b * rhs;
    result.a = a;
    return result;
  }

  // Adds another color component-wise and updates this color.
  Colour operator+=(Colour& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    a += other.a;
    return *this;
  }

  // Adds another color component-wise and updates this color.
  Colour operator+=(Colour other) {
    r += other.r;
    g += other.g;
    b += other.b;
    a += other.a;
    return *this;
  }

  // Multiplies the color by another color component-wise and updates this
  // color.
  Colour operator*=(Colour& other) {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    a *= other.a;
    return *this;
  }

  // Multiplies the color by another color component-wise and updates this
  // color.
  Colour operator*=(Colour other) {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    a *= other.a;
    return *this;
  }

  // Checks if any component of the color is greater than zero.
  bool bigger_than_zero() {
    if (r > 0 || g > 0 || b > 0) {
      return true;
    } else {
      return false;
    }
  }
};
