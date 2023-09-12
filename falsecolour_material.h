// This Material class maps the x,y,z components of the normal to the r,g,b
// components of the returned colour. A useful debug tool.

#pragma once

#include "material.h"

class FalseColour : public Material {
 public:
  Colour compute_once(Ray& viewer, Hit& hit, int recurse);
  Colour compute_per_light(Vector& viewer, Hit& hit, Vector& ldir);
};
