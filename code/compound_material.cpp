#include "compound_material.h"

// Constructor for the CompoundMaterial class, which takes the number of
// materials to combine.
CompoundMaterial::CompoundMaterial(int p_number) {
  number = p_number;
  for (int i = 0; i < number; i += 1) {
    materials[i] = 0;  // Initialise material array
  }
}

// Destructor for the CompoundMaterial class (no specific cleanup needed).
CompoundMaterial::~CompoundMaterial() {}

// Method to include a new material in the compound material.
void CompoundMaterial::include_material(Material* p_new) {
  for (int i = 0; i < number; i += 1) {
    if (materials[i] == 0) {
      materials[i] = p_new;
      return;
    }
  }
}

// The compute_once() method supplies the ambient term by combining all the
// ambient terms of all materials.
Colour CompoundMaterial::compute_once(Ray& viewer, Hit& hit, int recurse) {
  Colour result =
      Colour(0.0f, 0.0f, 0.0f);  // Initialize the result color to black

  for (int i = 0; i < number; i += 1) {
    if (materials[i] == 0) return result;  // Return if a material is missing

    result += materials[i]->compute_once(
        viewer, hit, recurse);  // Add ambient terms of all materials
  }

  return result;
}

// The compute_per_light() method supplies the diffuse and specular terms by
// combining them from all materials.
Colour CompoundMaterial::compute_per_light(Vector& viewer, Hit& hit,
                                           Vector& ldir) {
  Colour result;

  for (int i = 0; i < number; i += 1) {
    if (materials[i] == 0) return result;  // Return if a material is missing

    result += materials[i]->compute_per_light(
        viewer, hit, ldir);  // Add diffuse and specular terms of all materials
  }

  return result;
}
