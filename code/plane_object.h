#pragma once

#include "object.h"

class Plane : public Object {
 public:
  float a, b, c, d;

  Plane(float a, float b, float c, float d);

  Hit* intersection(Ray ray);
  void apply_transform(Transform& trans);
};
