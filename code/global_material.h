// The global material generates a reflection/refraction layer
#pragma once

#include "environment.h"
#include "material.h"

class GlobalMaterial : public Material {
 public:
  Colour reflect_weight;
  Colour refract_weight;
  float ior;
  Environment* environment;
  // void fresnel(Vector& view, Vector& normal, float etai, float etat, float&
  // kr, float ior);
  void fresnel(Vector& view, Vector& normal, float& kr, float etai, float etat,
               bool& entering);
  void refraction();
  bool refract_ray(Vector& view, Vector& normal, float ior, Vector& tray_dir,
                   bool& entering);

  GlobalMaterial(Environment* p_env, Colour p_reflect_weight,
                 Colour p_refract_weight, float ior);

  Colour compute_once(Ray& viewer, Hit& hit, int recurse);

  Colour compute_per_light(Vector& viewer, Hit& hit, Vector& ldir);
};
