
#include "checkered_plane_material.h"

#include <math.h>

#include "scene.h"

Checkered_Plane_Material::Checkered_Plane_Material(
    float _size, Colour _first_colour, Colour _second_Colour,
    Colour _outline_colour, Colour p_specular, float p_power) {
  specular = p_specular;
  first_colour = _first_colour;
  second_colour = _second_Colour;
  size = _size;
  outline_colour = _outline_colour;
  power = p_power;
}

// Gets the colour for the correct square or its outline colour
Colour Checkered_Plane_Material::get_colour(Hit& hit) {
  float outline_width = size / 20.0f;
  float x = hit.position.x;
  float z = hit.position.z;

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
Colour Checkered_Plane_Material::compute_once(Ray& viewer, Hit& hit,
                                              int recurse) {
  Colour result;
  Colour checkered = get_colour(hit);
  // float afc = 0.5;
  result += checkered * 0.5;
  return result;
}

// The compute_per_light() method supplies the diffuse and specular terms.
Colour Checkered_Plane_Material::compute_per_light(Vector& viewer, Hit& hit,
                                                   Vector& ldir) {
  Colour result;
  Colour checkered = get_colour(hit);
  // DIFFUSE
  float diff = hit.normal.dot(-ldir);
  result += checkered * diff;

  // Calculate the specular relfection term

  Vector reflect;

  hit.normal.reflection((-ldir), reflect);
  reflect.normalise();

  float H = reflect.dot(-viewer);

  if (H > 0.0) {
    // Apply the Phong specular flection model.
    float p = (float)pow(H, power);
    result += specular * p;
  }

  return result;
}
