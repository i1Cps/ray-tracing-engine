
/* Required c++ files are: demonstration1.cpp framebuffer.cpp linedrawer.cpp
 *
 * This will produce an image file called demonstration1.ppm. You can convert
 * this to a png file for viewing using
 * https://onlineconvertfree.com/convert-format/ppm-to-png/ or use the
 * application GIMP.
 *
 */

#include <math.h>

#include "framebuffer.h"
#include "linedrawer.h"

// This file outputs a circle of 32 line pointing away from the middle of the
// image (256,256)
int main(int argc, char *argv[]) {
  // Create a framebuffer size 512x512
  FrameBuffer *fb = new FrameBuffer(512, 512);

  // the initialise drawing the came with the file

  // Generate 64 radial lines around the center of the image.
  for (float i = 0; i < M_PI * 2; i += M_PI / 32.0f) {
    // Generate a simple 2D vector from origin (0,0) to point on circle
    float x = cos(i);
    float y = sin(i);

    // Draw a line, (256,256) is the middle of the output image, 48.0f moves
    // starting pixel for each line 48 pixels away from center Look at
    // output file to understand.
    draw_line(fb, 256 + (int)(48.0f * x), 256 + (int)(48.0f * y),
              256 + (int)(240.0f * x), 256 + (int)(240.0f * y));
  }

  // Output the framebuffer to demonstration1.ppm
  fb->writeRGBFile((char *)"demonstration1.ppm");

  return 0;
}
