// DirectionaLight is a child class of Light and implements a light
// with constant value in a given direction. The light has no position
// and can be treated as infinitely far away.

#pragma once
#include "light.h"

class DirectionalLight : public Light {
 public:
  Vector direction;
  Colour intensity;

  DirectionalLight();
  DirectionalLight(Vector dir, Colour col);

  bool get_direction(Vertex &surface, Vector &dir);
  void get_intensity(Vertex &surface, Colour &intensity);
};
