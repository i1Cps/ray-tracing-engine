// CompoundMaterial is a Material that applies multiple other materials to a
// surface. it can be used to combine a PhongMaterial and a GlobalMaterial on a
// single surface.

#pragma once

#include "material.h"

class CompoundMaterial : public Material {
 public:
  int number;
  Material* materials[10];

  // The constructor takes a single parameter, the maximum number of materials
  // to combine.
  CompoundMaterial(int p_number);
  ~CompoundMaterial();

  // Include material added another material to the compound material
  void include_material(Material* p_new);

  Colour compute_once(Ray& viewer, Hit& hit, int recurse);

  Colour compute_per_light(Vector& viewer, Hit& hit, Vector& ldir);
};
