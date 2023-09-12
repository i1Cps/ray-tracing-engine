// The FrameBuffer class creates a memory buffer that stores pixel information
// for an image.
#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

typedef struct {
  float red;
  float green;
  float blue;
  float depth;
} Pixel;

class FrameBuffer {
  Pixel *framebuffer;

 public:
  int width;
  int height;
  FrameBuffer(int w, int h);
  int plotPixel(int x, int y, float red, float green, float blue);
  int plotDepth(int x, int y, float depth);
  int getPixel(int x, int y, float &red, float &green, float &blue);
  int getDepth(int x, int y, float &depth);
  int writeRGBFile(char *filename);
  int writeDepthFile(char *filename);
};

#endif
