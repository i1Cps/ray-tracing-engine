#pragma once

#include "material.h"

class Checkered_Plane_Material : public Material {
 public:
  Colour specular;
  float power;
  Colour first_colour;
  Colour second_colour;
  float size;
  Colour outline_colour;

  Checkered_Plane_Material(float _size, Colour _first, Colour _secondColour,
                           Colour _outline_colour, Colour p_specular,
                           float p_power);
  Colour get_colour(Hit& hit);

  Checkered_Plane_Material() {}
  Colour compute_once(Ray& viewer, Hit& hit, int recurse);
  Colour compute_per_light(Vector& viewer, Hit& hit, Vector& ldir);
};
