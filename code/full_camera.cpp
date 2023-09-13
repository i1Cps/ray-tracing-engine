#include "full_camera.h"

#include "math.h"

// Empty constructor -- for now
FullCamera::FullCamera() {}

// Constructor called with field of view (f), camera position (p_position),
// look-at direction (p_lookat), and up direction (p_up) as arguments.
FullCamera::FullCamera(float f, Vertex& p_position, Vector& p_lookat,
                       Vector& p_up) {
  fov = f;
  position = p_position;
  lookat = p_lookat;
  up = p_up;

  // Calculate the camera coordinate vectors.
  w = position - lookat;
  w.normalise();
  // u = up ^ w;
  up.cross(w, right);
  right.normalise();
  // v = w ^ u;

  w.cross(right, v);
  // Stage one of camera setup is complete.
  // right.cross(lookat, up);
}

// Generates a ray with an offset (p_ox, p_oy) for a given pixel (p_x, p_y) and
// stores it in p_ray.
void FullCamera::get_ray_offset(int p_x, int p_y, float p_ox, float p_oy,
                                Ray& p_ray) {
  // Stage one of generating offset rays.
  // No implementation for now.
}

// Generates a ray for a given pixel (p_x, p_y) and stores it in p_ray.
void FullCamera::get_ray_pixel(int p_x, int p_y, Ray& ray) {
  // Stage one of generating rays for each pixel.

  // Get camera coorindate vector
  // new calculation for view coords
  float px = (-(float)p_x + (0.5 * (float)width)) / (float)width;
  float py = (-(float)p_y + (0.5 * (float)height)) / (float)height;

  // Vector3D dir = p.x * u + p.y * v - d * w;

  // Set ray position as camera origin
  ray.position.x = position.x;
  ray.position.y = position.y;
  ray.position.z = position.z;
  // ray.position.w = 1.0f;

  // ray.direction.x = dir.x;
  // ray.direction.y = dir.y;
  // ray.direction.z = dir.z;
  // ray.direction.normalise();

  // Calculate the ray's direction based on camera coordinate vectors.
  ray.direction = (px * right) + (py * v) - (fov * w);
  ray.direction.normalise();
  // get_ray_offset(ray.position.x, ray.position.y, position.x, position.y,
  // ray);
}

// Renders the scene using ray tracing and stores the result in the framebuffer.
void FullCamera::render(Environment& env, FrameBuffer& fb) {
  width = fb.width;
  height = fb.height;

  for (int y = 0; y < height; y += 1) {
    for (int x = 0; x < width; x += 1) {
      Ray ray;

      // Generate a ray for the current pixel.
      get_ray_pixel(x, y, ray);

      Colour colour;
      float depth;

      // Perform ray tracing to compute the color and depth for the current
      // pixel.
      env.raytrace(ray, 5, colour, depth);

      // Plot the pixel's color and depth in the framebuffer.
      fb.plotPixel(x, y, colour.r, colour.g, colour.b);
      fb.plotDepth(x, y, depth);
    }
    // Print a progress indicator for each row.
    cerr << "#" << flush;
  }
}
