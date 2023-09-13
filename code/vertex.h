// A four-element vector class with various operators and common functions

#pragma once

#include "vector.h"

class Vertex : public Vector {
 public:
  float w;  // The fourth component of the vector (w coordinate)

  // Default constructor: Initializes a vertex at the origin with full homogeneity.
  Vertex() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
    w = 1.0f;
  }

  // Constructor with x, y, z, and w values: Initializes a vertex with specified components.
  Vertex(float x_coord, float y_coord, float z_coord, float hom) {
    x = x_coord;
    y = y_coord;
    z = z_coord;
    w = hom;
  }

  // Constructor with x, y, and z values: Initializes a vertex with specified components and full homogeneity.
  Vertex(float x_coord, float y_coord, float z_coord) {
    x = x_coord;
    y = y_coord;
    z = z_coord;
    w = 1.0f;
  }

  // Addition operator for adding a vector to a vertex.
  Vertex operator+(Vector const& other_vector) {
    Vertex result;
    result.x = this->x + other_vector.x;
    result.y = this->y + other_vector.y;
    result.z = this->z + other_vector.z;
    result.w = this->w;
    return result;
  }

  // Subtraction operator for subtracting a vector from a vertex.
  Vertex operator-(Vector const& other_vector) {
    Vertex result;
    result.x = this->x - other_vector.x;
    result.y = this->y - other_vector.y;
    result.z = this->z - other_vector.z;
    result.w = this->w;
    return result;
  }

  // Negation operator for negating all components of a vertex
  Vertex operator-() {
    Vertex result;
    result.x = -this->x;
    result.y = -this->y;
    result.z = -this->z;
    result.w = -this->w;

    return result;
  }
};