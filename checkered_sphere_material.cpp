
#include "checkered_sphere_material.h"

#include <math.h>

#include "scene.h"

Checkered_Sphere_Material::Checkered_Sphere_Material(
    float _size, Colour _first_colour, Colour _second_Colour,
    Colour _outline_colour, Colour p_specular, float p_power) {
  specular = p_specular;
  first_colour = _first_colour;
  second_colour = _second_Colour;
  size = _size;
  outline_colour = _outline_colour;
  power = p_power;
}

std::pair<float, float> Checkered_Sphere_Material::spherical_map(
    Vector hit_position) {
  float hpx = hit_position.x;
  float hpy = hit_position.y;
  float hpz = hit_position.z;
  // Compute the azimuthal angle
  // -π < theta <= π
  // angle increases clockwise as viewed from above,
  // which is opposite of what we want, but we'll fix it later.

  float theta = atan2f(hpx, hpz);

  // Vec is the vector pointing from the sphere's origin (the world origin)
  // to the point, which will also happen to be exactly equal to the sphere's
  // radius.
  Vector hp = hit_position;
  float radius = hp.length();

  // Compute the polar angle
  // 0 <= phi <= π
  float phi = acosf(hpy / radius);

  // -0.5 < raw_u <= 0.5
  float raw_u = theta / (2 * M_PI);

  // 0 <= u < 1
  // here's also where we fix the direction of u. Subtract it from 1,
  // so that it increases counterclockwise as viewed from above.
  float u = 1 - (raw_u + 0.5);

  // We want v to be 0 at the south pole of the sphere,
  // and 1 at the north pole, so we have to "flip it over"
  // by subtracting it from 1.
  float v = 1 - phi / M_PI;
  return std::make_pair(u, v);
}

// Gets the colour for the correct square or its outline colour
Colour Checkered_Sphere_Material::get_colour(Hit& hit) {
  float outline_width = 0.0000f;
  std::pair<float, float> uv = spherical_map(hit.position);
  float x = uv.first;
  float z = uv.second;

  int ix = floor(x / size);
  int iz = floor(z / size);
  float fx = x / size - ix;
  float fz = z / size - iz;

  float width = 0.5 * outline_width / size;
  bool in_outline =
      (fx < width || fx > 1.0 - width) || (fz < width || fz > 1.0 - width);
  if ((ix + iz) % 2 == 0) {
    if (!in_outline) return (first_colour);
  } else {
    if (!in_outline) return (second_colour);
  }
  return (outline_colour);
}

// The compute_once() method supplies the ambient term.
Colour Checkered_Sphere_Material::compute_once(Ray& viewer, Hit& hit,
                                               int recurse) {
  Colour result;
  Colour checkered = get_colour(hit);
  // float afc = 0.5;
  result += checkered * 0.5;
  return result;
}

// The compute_per_light() method supplies the diffuse and specular terms.
Colour Checkered_Sphere_Material::compute_per_light(Vector& viewer, Hit& hit,
                                                    Vector& ldir) {
  Colour result;

  Colour checkered = get_colour(hit);
  // DIFFUSE
  float diff = hit.normal.dot(-ldir);
  result += checkered * diff;

  // SPECULAR

  Vector reflect;

  hit.normal.reflection((-ldir), reflect);
  reflect.normalise();

  float H = reflect.dot(-viewer);

  if (H > 0.0) {
    float p = (float)pow(H, power);
    result += specular * p;
  }

  return result;
}
