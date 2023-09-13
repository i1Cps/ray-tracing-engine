#pragma once

#include <math.h>

#include "object.h"

class Quadratic : public Object {
 public:
  float a, b, c, d, e, f, g, h, i, j;

  Quadratic(float a_, float b_, float c_, float d_, float e_, float f_,
            float g_, float h_, float i_, float j_);

  Hit* intersection(Ray ray);
  void apply_transform(Transform& trans);
};
