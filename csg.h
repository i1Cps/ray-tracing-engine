
#pragma once

#include <math.h>

#include "colour.h"
#include "environment.h"
#include "hit.h"
#include "light.h"
#include "object.h"
#include "ray.h"

class Csg : public Object {
 public:
  Object* obj1;
  Object* obj2;
  int operation_;

  // TAKES In 2 objects
  Csg(Object* object1, Object* object2, int operation);
  Hit* intersection(Ray ray);
  Hit* implement_csg(Hit* hit1, Hit* hit2);
  int comparison_table(int operation, bool entering1, bool entering2, float t1,
                       float t2);
  // Hit* add_new_hit(Hit* main_hits, Hit* hit);
};