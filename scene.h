#pragma once

#include "colour.h"
#include "environment.h"
#include "hit.h"
#include "light.h"
#include "object.h"
#include "ray.h"

// Scene is a class that is used to build a scene database of objects
// and lights and then trace a ray through it.
class Scene : public Environment {
 public:
  Object *object_list;
  Light *light_list;

  Scene();

  // Filter the list of returned hits to the closest +ve
  Hit *select_first(Hit *list);

  // Trace a ray through the scene and find the closest if any object
  // intersection in front of the ray.
  Hit *trace(Ray ray);

  // Trace a ray through the scene and return its colour. This function is
  // important for recursion during the reflection/refraction tree
  void raytrace(Ray ray, int recurse, Colour &colour, float &depth);

  // Raytrace a shadow ray.
  bool shadowtrace(Ray, float limit);

  void add_object(Object *obj);
  void add_light(Light *light);
};
