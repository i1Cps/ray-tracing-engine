// Environment is the base class for raytracing. We use this in material the
// classes to do recursion as that allows the Scene class, which is derived from
// this, to depend (indirectly) on Material.

#pragma once

#include "colour.h"
#include "ray.h"

class Environment {
 public:
  // Shoot a ray into the environment and get the colour and depth.
  // recurse indicates the level of recursion permitted.
  virtual void raytrace(Ray ray, int recurse, Colour& colour, float& depth) {
    colour.r = 0.0f;
    colour.g = 0.0f;
    colour.b = 0.0f;
    depth = 100000000.0f;
  }

  // Raytrace a shadow ray. returns true if intersection found between 0 and
  // limit along ray.
  virtual bool shadowtrace(Ray, float limit) { return false; }
};
