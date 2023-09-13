// Implementation file for the Sphere class, representing a simple sphere object
// in a 3D scene.
#include "sphere_object.h"

#include <math.h>

// Constructor: Initialize the Sphere object with a center and radius.
Sphere::Sphere(Vertex c, float r) {
  center = c;
  radius = r;
}

// Calculate the intersection between an input ray and this sphere.
// Returns a pointer to a Hit object if an intersection occurs, or nullptr if no
// intersection.
Hit* Sphere::intersection(Ray ray) {
  Vector ro;
  float small_e = 0.00000000000;

  // Offset ray by sphere position
  // equivalent to transforming ray into local sphere space

  ro.x = ray.position.x - center.x;
  ro.y = ray.position.y - center.y;
  ro.z = ray.position.z - center.z;

  float a = (float)ray.direction.dot(ray.direction);
  float b = (float)(2.0 * ray.direction.dot(ro));
  float c = (float)ro.dot(ro) - radius * radius;

  float disc = b * b - 4 * a * c;

  if (disc < 0.0f) {
    return 0;  // A negative value indicates no intersection.
  }

  // An intersection has been found, record details Hit objects
  float ds = sqrtf(disc);

  float t0 = (-b - ds) / 2.0f;
  float t1 = (-b + ds) / 2.0f;

  Hit* hit0 = new Hit();
  hit0->what = this;
  hit0->t = t0;
  hit0->entering = true;

  // Compute the position and normal at the intersection point.
  hit0->position = (ray.position + hit0->t * ray.direction) +
                   Vector(small_e, small_e, small_e);
  hit0->normal = hit0->position - center;
  hit0->normal.normalise();

  // Ensure the normal points in the correct direction.
  if (hit0->normal.dot(ray.direction) > 0.0) {
    hit0->normal.negate();
  }

  Hit* hit1 = new Hit();
  hit1->what = this;
  hit1->t = t1;
  hit1->entering = false;

  // Compute the position and normal at the second intersection point.
  hit1->position = ray.position + hit1->t * ray.direction;
  hit1->normal = hit1->position - center;
  hit1->normal.normalise();

  // Ensure the normal points in the correct direction.
  if (hit1->normal.dot(ray.direction) > 0.0) {
    hit1->normal.negate();
  }

  // Create a linked list of hits for multiple intersections.
  hit0->next = hit1;
  hit1->next = 0;

  return hit0;
}

void Sphere::apply_transform(Transform& transform) { transform.apply(center); }