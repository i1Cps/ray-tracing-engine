// Ray is a class to store and maniplulate 3D rays.

#pragma once

#include <iostream>
using namespace std;

#include "vector.h"
#include "vertex.h"

class Ray {
 public:
  Vertex position;
  Vector direction;

  Ray() {}
  // Constructor for ray, takes position and direction
  Ray(Vertex p, Vector d) {
    position = p;
    direction = d;
  }

  // Debug operator
  friend ostream& operator<<(ostream& os, const Ray& r) {
    os << "Ray{[" << r.position.x << "," << r.position.y << "," << r.position.z
       << "],[" << r.direction.x << "," << r.direction.y << "," << r.direction.z
       << "]}\n";
    return os;
  }
};
