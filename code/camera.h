// Camera is the base class for cameras.
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "environment.h"
#include "framebuffer.h"
#include "ray.h"

class Camera {
 public:
  // Empty constructor
  Camera() {}

  // Given an environment (typically the Scene class, fill in the framebuffer
  // pixels, both colour and depth)
  virtual void render(Environment& env, FrameBuffer& fb) {}
};

#endif
