// A simple Phong based lighting model.

#include "phong_material.h"

#include <math.h>

#include "scene.h"

Phong::Phong(Colour p_ambient, Colour p_diffuse, Colour p_specular,
             float p_power) {
  ambient = p_ambient;    // Ambient reflection coefficient
  diffuse = p_diffuse;    // Diffuse reflection coefficient
  specular = p_specular;  // Specular reflection coefficient
  power = p_power;        // Shininess or specular power
}

// The compute_once() method supplies the ambient term.
Colour Phong::compute_once(Ray& viewer, Hit& hit, int recurse) {
  Colour result;
  // ambient reflection coefficient
  float afc = 1;
  result += ambient * afc;
  return result;
}

// The compute_per_light() method supplies the diffuse and specular terms.
Colour Phong::compute_per_light(Vector& viewer, Hit& hit, Vector& ldir) {
  Colour result;

  // DIFFUSE reflection
  float diff =
      hit.normal.dot(-ldir);  // Calculate the cosine of the angle between light
                              // direction and surface normal
  result += diffuse * diff;   // Apply the diffuse reflection coefficient

  // SPECULAR reflection (Phong reflection model)

  Vector reflect;

  hit.normal.reflection((-ldir), reflect);  // Calculate the reflection vector
  reflect.normalise();

  float H = reflect.dot(
      -viewer);  // Calculate the half-vector between viewer and light direction

  // Apply specular reflection based on the Phong model
  if (H > 0.0) {
    float p = (float)pow(
        H, power);  // Compute the specular term using the shininess (power)
    result += specular * p;  // // Apply the specular reflection coefficient
  }

  return result;
}
