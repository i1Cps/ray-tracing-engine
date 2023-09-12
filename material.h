// Material is the base class for materials.

#pragma once

#include "colour.h"
#include "hit.h"
#include "ray.h"

class Material {
 public:
  // Compute_once is called once per intersection
  virtual Colour compute_once(Ray &viewer, Hit &hit, int recurse) {
    Colour result;
    result.r = 0.0f;
    result.g = 0.0f;
    result.b = 0.0f;
    return result;
  }

  // Compute_per_light is called for each light that reaches a surface
  virtual Colour compute_per_light(Vector &viewer, Hit &hit, Vector &ldir) {
    Colour result;
    result.r = 0.0f;
    result.g = 0.0f;
    result.b = 0.0f;
    return result;
  }

  // I'll need additional material methods to support Photon-mapping, coming
  // soon.
};
