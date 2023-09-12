#include "simple_camera.h"

SimpleCamera::SimpleCamera() { fov = 0.5; }

// Constructor called with field of view as argument
SimpleCamera::SimpleCamera(float p_f) { fov = p_f; }

// Generates a ray for a given pixel (x, y) and stores it in p_ray.
void SimpleCamera::get_ray_pixel(int p_x, int p_y, Ray& p_ray) {
  // PixelNDc (normalized device coordinates)
  float fx = ((float)p_x + 0.5f) / (float)width;
  float fy = ((float)p_y + 0.5f) / (float)height;

  // Equals 0 cah camera origin is (0,0,0) for "simpleCamera" class
  p_ray.position.x = 0.0f;
  p_ray.position.y = 0.0f;
  p_ray.position.z = 0.0f;
  p_ray.position.w = 1.0f;
  // 0.5 because its the middle of the pixel
  // direction between a and b is pos(b) - pos(a)
  // or as they put it:
  // dir.x is change in x
  // dir.y is change in y
  // dir.z is fov
  // then normalize
  p_ray.direction.x = (fx - 0.5f);
  p_ray.direction.y = (0.5f - fy);
  p_ray.direction.z = fov;
  p_ray.direction.normalise();
}

// Renders the scene using ray tracing and stores the result in the framebuffer.
void SimpleCamera::render(Environment& env, FrameBuffer& fb) {
  // Set the camera's width and height based on the framebuffer.
  width = fb.width;
  height = fb.height;

  // Loop through all pixels in the framebuffer.
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