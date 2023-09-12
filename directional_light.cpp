#include "directional_light.h"

// Constructor for the DirectionalLight class (default constructor)
DirectionalLight::DirectionalLight() {
  Light();  // Initialize as a Light object (if Light is the base class)
}

// Constructor for the DirectionalLight class with direction and color
// parameters
DirectionalLight::DirectionalLight(Vector dir, Colour col) {
  Light();  // Initialize as a Light object (if Light is the base class)

  direction = dir;        // Set the direction of the directional light
  direction.normalise();  // Normalize the direction vector
  intensity = col;        // Set the intensity (color) of the directional light
}

// Get the direction of the light at a given surface point
bool DirectionalLight::get_direction(Vertex &surface, Vector &dir) {
  dir =
      direction;  // Set the direction of the light to the pre-defined direction

  return true;  // Indicate that the direction was successfully obtained
}

// Get the intensity (color) of the light at a given surface point
void DirectionalLight::get_intensity(Vertex &surface, Colour &level) {
  level = intensity;  // Set the intensity (color) of the light to the
                      // pre-defined intensity
}