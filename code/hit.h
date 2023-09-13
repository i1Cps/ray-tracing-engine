// Hit is a class to store and maniplulate information about an intersection
// between a ray and an object.

#pragma once

#include <iostream>
using namespace std;

#include "vector.h"
#include "vertex.h"

class Object;

class Hit {
 public:
  static Hit *free_pool;
  static int allocated;
  static int pool_size;

  float t;          // The intersection distance
  bool entering;    // True if entering an object, false if leaving
  Hit *next;        // The next hit in a list along a ray
  Object *what;     // the object that has been hit
  Vertex position;  // the position of intersection
  Vector normal;    // the normal at the point of intersection

  void *operator new(size_t size);
  void operator delete(void *p);
};
