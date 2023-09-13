// Implementation file for the Plane class, representing a simple plane object
// in a 3D scene.

#include "plane_object.h"

// Constructor: Initialize the Plane object with coefficients a, b, c, and d for
// the plane equation ax + by + cz + d = 0.
Plane::Plane(float p_a, float p_b, float p_c, float p_d) {
  a = p_a;
  b = p_b;
  c = p_c;
  d = p_d;
}

// Calculate the intersection between a ray and this plane.
// Returns a pointer to a Hit object if an intersection occurs, or nullptr if no
// intersection.
Hit* Plane::intersection(Ray ray) {
  float U = a * ray.position.x + b * ray.position.y + c * ray.position.z + d;
  float V = a * ray.direction.x + b * ray.direction.y + c * ray.direction.z;

  if (V == 0.0f) {
    // Ray is parallel to plane
    if (U < 0.0f) {
      // Ray originates inside the plane
      Hit* hit1 = new Hit();
      Hit* hit2 = new Hit();
      hit1->entering = true;
      hit1->t =
          -10000000000.0f;  // Negative infinity to represent inside the plane.
      hit1->what = this;
      hit2->entering = false;
      hit2->t =
          10000000000.0f;  // POSITIVE infinity to represent outside the plane.
      hit2->what = this;
      hit1->next = hit2;
      hit2->next = 0;
      return hit1;
    }

    // Ray originates outside the plane, no intersection.
    return 0;
  }
  if (V > 0) {
    // Ray intersects the plane.
    float t = U / -V;
    Hit* hit1 = new Hit();
    Hit* hit2 = new Hit();
    hit1->entering = true;
    hit1->t =
        -10000000000.0f;  // Negative infinity to represent inside the plane.
    hit1->what = this;
    hit2->entering = false;
    hit2->t = t;  // Intersection point along the ray.
    hit2->position = ray.position + t * ray.direction;
    hit2->normal = Vector(a, b, c);

    // Ensure the normal points in the correct direction.
    if (hit2->normal.dot(ray.direction) > 0.0) {
      hit2->normal.negate();
    }
    hit2->what = this;
    hit1->next = hit2;
    hit2->next = 0;
    return hit1;
  } else {
    float t = U / -V;
    Hit* hit1 = new Hit();
    Hit* hit2 = new Hit();
    hit1->entering = true;
    hit1->t = t;  // infinity
    hit1->position = ray.position + t * ray.direction;
    hit1->normal = Vector(a, b, c);

    // Ensure the normal points in the correct direction.

    if (hit1->normal.dot(ray.direction) > 0.0) {
      hit1->normal.negate();
    }
    hit1->what = this;
    hit2->entering = false;
    hit2->t = 10000000000.0f;  // Infinity
    hit2->what = this;
    hit1->next = hit2;
    hit2->next = 0;
    return hit1;
  }
}

// Apply a transformation to the plane using a 4x4 transformation matrix.
void Plane::apply_transform(Transform& trans) {
  Transform ti = trans.inverse().transpose();
  Vertex v = Vertex(a, b, c, d);

  ti.apply(v);

  a = v.x;
  b = v.y;
  c = v.z;
  d = v.w;
}