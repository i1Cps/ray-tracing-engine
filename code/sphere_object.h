// Simple sphere object

#pragma once

#include "object.h"

class Sphere : public Object {
  Vertex center;
  float radius;

 public:
  Sphere(Vertex c, float r);
  Hit* intersection(Ray ray);
  void apply_transform(Transform& trans);
};
