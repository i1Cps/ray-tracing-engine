// Object is the base class for objects.
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "hit.h"
#include "material.h"
#include "ray.h"
#include "transform.h"

class Object {
 public:
  Object *next;
  Material *material;

  Object() {
    next = (Object *)0;
    material = (Material *)0;
  }

  // Specify the material this object uses
  virtual void set_material(Material *p_m) { material = p_m; }

  // Given a ray, if this object intersects it, return all the points of
  // intersection resturn null if no intersections
  virtual Hit *intersection(Ray ray) { return 0; }

  // apply a transform to this object.
  virtual void apply_transform(Transform &trans) { return; }
};

#endif
