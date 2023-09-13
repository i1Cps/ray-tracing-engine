#include "scene.h"

Scene::Scene() {
  object_list = 0;
  light_list = 0;
}

// Checks if a point is a shadow by using a shadow ray
bool Scene::shadowtrace(Ray ray, float limit) {
  // Loop over all objects in the scene and check for intersection
  // and returns the first intersection
  Object *objects = this->object_list;

  while (objects != 0) {
    Hit *hit = this->select_first(objects->intersection(ray));

    if (hit != 0) {
      // Ensure intersection point is in front of the rays origin (to avoid self
      // shadowing) Also ensure the itnersection is within the limit, dont want
      // shadow ray travelling too far else there no point
      if ((hit->t > 0.00000001f) && (hit->t < limit)) {
        delete hit;
        return true;
      }
      delete hit;
    }

    objects = objects->next;
  }

  return false;
}

// Trace a ray through the scene and find the closest intersection in front of
// the ray.
Hit *Scene::trace(Ray ray) {
  // Initialise best hit pointer, this pointer keeps track of the closest
  // intersection found during the ray tracing process.
  Hit *best_hit = 0;

  // Initialise a object pointer to point to the first object in the scene
  Object *objects = this->object_list;

  // Loop over all objects in the scene get first intersections if one occurs
  // for that object
  while (objects != 0) {
    Hit *hit = this->select_first(objects->intersection(ray));
    // Simply keep track of the best intersection (smallest t)over all objects
    // in loop
    if (hit != 0) {
      if (best_hit == 0) {
        best_hit = hit;

      } else if (hit->t < best_hit->t) {
        delete best_hit;
        best_hit = hit;
      } else {
        delete hit;
      }
    }

    objects = objects->next;
  }

  return best_hit;
}

// Filter the list of returned hits and return the closest positive one
Hit *Scene::select_first(Hit *list) {
  // Simple linked list logic to return smallest t property on all intersections
  Hit *result = 0;

  while (list != 0) {
    if (list->t >= 0.0f) {
      result = list;
      list = list->next;
      break;
    }

    Hit *temp = list;
    list = list->next;
    delete temp;
  }

  while (list != 0) {
    Hit *temp = list;
    list = list->next;
    delete temp;
  }

  return result;
}

// Trace a ray through the scene and return its colour. This function is
// important for recursion during the reflection/refraction tree
void Scene::raytrace(Ray ray, int recurse, Colour &colour, float &depth) {
  Object *objects = object_list;
  Light *lights = light_list;

  // A default colour if we hit nothing.
  colour.r = 0.0f;
  colour.g = 0.0f;
  colour.b = 0.0f;
  colour.a = 0.0f;
  depth = 0.0f;

  // First step, find the closest intersection
  Hit *best_hit = this->trace(ray);

  // If we found a intersection then compute the colour we should see
  if (best_hit != 0) {
    depth = best_hit->t;
    colour =
        colour + best_hit->what->material->compute_once(
                     ray, *best_hit,
                     recurse);  // This will be called on the global components
                                // such as ambient or reflect/refract

    // Next, compute the light contribution for each light in the scene.
    // Iterate through each light source in the scene
    Light *light = light_list;
    while (light != (Light *)0) {
      Vector viewer;
      Vector ldir;
      viewer = ray.position - best_hit->position;
      viewer.normalise();
      bool lit;
      lit = light->get_direction(best_hit->position, ldir);
      if (ldir.dot(best_hit->normal) > 0) {
        lit = false;  // Light is facing wrong way.
      }

      // Shadow check here, if lit==true and in shadow, set lit=false

      if (lit) {
        Ray shadow_ray;

        shadow_ray.direction = -ldir;

        shadow_ray.position =
            best_hit->position + (0.0001f * shadow_ray.direction);

        if (this->shadowtrace(shadow_ray, 1000000000.0f)) {
          lit = false;  // There's a shadow so no lighting, if realistically
                        // close.
        }
      }
      // If not a shadow, calculate light intensity (calculated differently
      // depending on the material)
      if (lit) {
        Colour intensity;

        light->get_intensity(best_hit->position, intensity);

        colour =
            colour + intensity * best_hit->what->material->compute_per_light(
                                     viewer, *best_hit,
                                     ldir);  // This is the per light local
                                             // contrib e.g. diffuse, specular
      }

      light = light->next;
    }

    delete best_hit;
  } else {
    colour.r = 0.0f;
    colour.g = 0.0f;
    colour.b = 0.0f;
    colour.a = 1.0f;
  }
}
// Add object to the scene, and thus the list of objects.
void Scene::add_object(Object *obj) {
  obj->next = this->object_list;
  this->object_list = obj;
}

// Add light to the scen, and thus the list of light sources.
void Scene::add_light(Light *light) {
  light->next = this->light_list;
  this->light_list = light;
}