#include "global_material.h"

#include <math.h>

#include "vector.h"

// This file defines the GlobalMaterial class for handling reflection,
// refraction, and lighting computations in a ray tracing engine. It provides
// functions to calculate reflection and refraction rays, as well as to compute
// material properties based on lighting conditions.

GlobalMaterial::GlobalMaterial(Environment* p_env, Colour p_reflect_weight,
                               Colour p_refract_weight, float p_ior) {
  reflect_weight = p_reflect_weight;
  refract_weight = p_refract_weight;
  // Index of refraction values can be found at
  // https://www.physlink.com/reference/indicesofrefraction.cfm Its 1 for vaccum
  // and 1.0003 for air etc... 1.52 for glass
  ior = p_ior;
  environment = p_env;
}

// Function that calculates refraction ray direction and calculates if there is
// total inter reflection
bool GlobalMaterial::refract_ray(Vector& wo, Vector& normal, float ior,
                                 Vector& tray_dir, bool& entering) {
  Vector normal_ = normal;
  // Relative index of refraction = vacuum IOR to object IOR
  float ior_in = ior;
  float ior_out = 1.0f;
  float n = ior_in / ior_out;

  // If entering the refractive material reverse the normal in direction of
  // initial ray
  if (entering) {
    normal_ = -normal_;
  }
  float cos_theta_i = normal_.dot(wo);

  // Check if we are hitting an object from the inside, if we are make the
  // following changes
  if (cos_theta_i < 0) {
    cos_theta_i = -cos_theta_i;
    normal_ = -normal_;
    n = 1 / n;
  }

  float cos_theta_t_squared =
      (1.0f - (pow(1 / n, 2)) * (1.0f - pow(cos_theta_i, 2)));

  // Check if total inter reflection occurs, if cos_theta_t_squared is negative,
  // cos_theta_t is imaginary. theres no refraction ray
  if (cos_theta_t_squared < 0.0f) {
    tray_dir = wo;
    return true;
  }
  // Calculats refraction ray direction
  tray_dir = (1 / n * wo) -
             (((1 / n) * cos_theta_i) - sqrt(cos_theta_t_squared)) * normal_;
  return false;
}

void GlobalMaterial::fresnel(Vector& view, Vector& normal, float& kr,
                             float etai, float etat, bool& entering) {
  // Negate normal because we are dealing with refraction not reflection
  Vector normal_ = -normal;
  float cos_theta_i = normal_.dot(view);
  float n = etat / etai;
  float cos_theta_t_squared =
      (1.0f - (pow(1 / n, 2)) * (1.0f - pow(cos_theta_i, 2)));

  // Follow snells law
  if (cos_theta_t_squared < 0.0f) {
    cos_theta_t_squared = 0;
  }
  float cos_theta_t = sqrt(cos_theta_t_squared);
  float rpar = (etai * cos_theta_i - etat * cos_theta_t) /
               (etai * cos_theta_i + etat * cos_theta_t);
  float rper = (etat * cos_theta_i - etai * cos_theta_t) /
               (etat * cos_theta_i + etai * cos_theta_t);
  kr = (pow(rpar, 2) + pow(rper, 2)) / 2;
}

// Reflection and recursion computation
Colour GlobalMaterial::compute_once(Ray& viewer, Hit& hit, int recurse) {
  Colour result;
  // If recurse is zero we end recursion loop
  if (recurse == 0) {
    return result;
  }
  // Checks if user wants any reflection or refraction
  if (reflect_weight.bigger_than_zero() || refract_weight.bigger_than_zero()) {
    // Create reflection ray and calculate direction and position
    Ray rray;
    Colour reflection;
    Colour refraction;
    Vector wo = viewer.direction;
    float kr, kt;

    // Set reflection ray position and direction
    hit.normal.reflection(wo, rray.direction);
    rray.position = hit.position + 0.1 * rray.direction;
    // Not to be confused with recurse, this float handles the depth values of
    // pixels
    float depth;
    // When IOR is equal to 0 it means there is no refraction
    if (ior == 0) {
      // Raytrace reflection ray
      environment->raytrace(rray, recurse - 1, reflection, depth);
      // reflection * reflect_weight;
      result += reflection * reflect_weight;
      return result;
    } else {
      // If ior > 0 this means theres reflection possibly refraction
      // Check for transparant inter reflection
      Ray tray;
      bool tir = refract_ray(wo, hit.normal, ior, tray.direction, hit.entering);
      if (tir) {
        // If there is tir set kr to 1 because it means theres only reflection
        // std::cout << "tir" << recurse << std::endl;
        kr = 1;
        kt = 0;
        // Raytrace reflection ray
        environment->raytrace(rray, recurse - 1, reflection, depth);
        // Apply fresnel reflection coefficient and reflection_weight (made by
        // user) to colour returned by raytrace() and add this colour to results
        result += reflection * reflect_weight * kr;
        return result;
      } else {
        // Calculate kr and kt values
        fresnel(wo, hit.normal, kr, 1, ior, hit.entering);
        kt = 1 - kr;
        // Raytrace reflection ray
        environment->raytrace(rray, recurse - 1, reflection, depth);
        // Compute refraction ray position and direction
        tray.position = hit.position + 0.0001 * tray.direction;
        // Raytrace refraction ray
        environment->raytrace(tray, recurse - 1, refraction, depth);
        // Apply fresnel reflection coefficient , fresnel refraction
        // coefficient, reflection_weight and refraction_weight to colour
        // returned by raytrace() and add this colour to results
        result += (reflection * kr * reflect_weight) +
                  (refraction * kt * refract_weight);
      }
    }
  }
  // Else theres just diffusion so return 0
  else {
    std::cout << "no reflect or refract" << std::endl;
    return result;
  }
  return result;
}

Colour GlobalMaterial::compute_per_light(Vector& viewer, Hit& hit,
                                         Vector& ldir) {
  Colour result;

  result.r = 0.0f;
  result.g = 0.0f;
  result.b = 0.0f;

  return result;
}
