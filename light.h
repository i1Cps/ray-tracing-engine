// Light is the base class for lights.

#pragma once

#include "colour.h"
#include "vector.h"
#include "vertex.h"

class Light {
 public:
  Light *next;

  Light() { next = (Light *)0; }

  // Get the direction towards the light at the point on the surface
  // should return true if the surface is in front of the light
  // and false if it's behind and not illuminated.
  virtual bool get_direction(Vertex &surface, Vector &dir) { return false; }

  // Get the intensity of the light in the direction of the surface
  virtual void get_intensity(Vertex &surface, Colour &intensity) {}

  // I'll need additional light methods to support Photon-mapping, coming soon.
};
