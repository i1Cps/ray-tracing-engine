// This class maps the x,y,z components of the normal to the r,g,b components
// of the returned colour. A useful debug tool. -1 to +1 maps to 0 to 1

#include "falsecolour_material.h"

#include <math.h>

// The compute_once() method maps the normal to the colour to aid debug.
Colour FalseColour::compute_once(Ray& viewer, Hit& hit, int recurse) {
  Colour result;
  result.r = (hit.normal.x + 1.0f) * 0.5f;
  result.g = (hit.normal.y + 1.0f) * 0.5f;
  result.b = (hit.normal.z + 1.0f) * 0.5f;
  return result;
}

// The compute_per_light() method makes no contribution.
Colour FalseColour::compute_per_light(Vector& viewer, Hit& hit, Vector& ldir) {
  Colour result = Colour(0.0f, 0.0f, 0.0f);

  return result;
}
