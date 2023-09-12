// Full camera allows a camera to be placed in space with a lookat and up
// direction as well as the field of view. It loops over the pixels in a
// framebuffer and computes a ray that is then passed to the environment.

#ifndef _FULL_CAMERA_H_
#define _FULL_CAMERA_H_

#include "camera.h"

class FullCamera : public Camera {
 public:
  int width;
  int height;
  float fov;
  Vertex position;
  Vector lookat;
  Vector up;
  Vector right;
  Vector v;
  Vector w;

  FullCamera();

  FullCamera(float p_f, Vertex& p_position, Vector& p_lookat, Vector& p_up);

  void get_ray_offset(int p_x, int p_y, float p_ox, float p_oy, Ray& p_ray);

  void get_ray_pixel(int p_x, int p_y, Ray& ray);

  void render(Environment& env, FrameBuffer& fb);
};

#endif
