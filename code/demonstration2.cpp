/* Required c++ files are: demonstration2.cpp framebuffer.cpp linedrawer.cpp
 * polymesh_object.cpp hit.cpp
 *
 * This will produce an image file called demonstration2.ppm. You can convert
 * this to a png file for viewing using
 * https://onlineconvertfree.com/convert-format/ppm-to-png/ or use the
 * application GIMP.
 *
 */

#include "framebuffer.h"
#include "linedrawer.h"
#include "polymesh_object.h"

// This file loads a triangle mesh object, then calls the linedrawer function to
// render it as a 2D image in a ppm file.
int main(int argc, char *argv[]) {
  // Create a framebuffer for image size (1024,1024)
  FrameBuffer *fb = new FrameBuffer(1024, 1024);

  // The following transform allows 4D homogeneous coordinates to be
  // transformed. It moves the supplied teapot model to somewhere visible.
  Transform *transform =
      new Transform(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, -2.7f, 0.0f, 1.0f,
                    0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);

  // Read in the teapot.ply model
  PolyMesh *pm = new PolyMesh((char *)"teapot_smaller.ply", false);
  pm->apply_transform(*transform);

  // For each triangle in the model,
  for (int i = 0; i < pm->triangle_count; i += 1) {
    // The following code projects each point from the .ply file onto the 2D
    // image from 3D space.
    float x0 =
        (pm->vertex[pm->triangle[i][0]].x / pm->vertex[pm->triangle[i][0]].z) *
            700.0 +
        512.0;
    float y0 =
        (pm->vertex[pm->triangle[i][0]].y / pm->vertex[pm->triangle[i][0]].z) *
            -700.0 +
        256.0;
    float x1 =
        (pm->vertex[pm->triangle[i][1]].x / pm->vertex[pm->triangle[i][1]].z) *
            700.0 +
        512.0;
    float y1 =
        (pm->vertex[pm->triangle[i][1]].y / pm->vertex[pm->triangle[i][1]].z) *
            -700.0 +
        256.0;
    float x2 =
        (pm->vertex[pm->triangle[i][2]].x / pm->vertex[pm->triangle[i][2]].z) *
            700.0 +
        512.0;
    float y2 =
        (pm->vertex[pm->triangle[i][2]].y / pm->vertex[pm->triangle[i][2]].z) *
            -700.0 +
        256.0;

    // Then connect the 3 points for eaech triangle and draw to the scene ppm
    // file.
    draw_line(fb, (int)x0, (int)y0, (int)x1, (int)y1);
    draw_line(fb, (int)x1, (int)y1, (int)x2, (int)y2);
    draw_line(fb, (int)x2, (int)y2, (int)x0, (int)y0);
    printf(".");
  }

  // Output the framebuffer.
  fb->writeRGBFile((char *)"demonstration2.ppm");

  return 0;
}
