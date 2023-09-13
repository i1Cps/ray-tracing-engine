// NOTES NOTES NOTES NOTES NOTES NOTES NOTES NOTES NOTES
// top left is (0,0)
// bottom right is (512,512)
// when gradient > 1 it used draw_y func

#include "linedrawer.h"

#include <iostream>

int draw_x_line(FrameBuffer *fb, int sx, int sy, int ex, int ey) {
  int dir = 1;
  if (sx > ex) {
    dir = -1;
  }
  int dy = ey - sy;
  int dx = ex - sx;
  int x = sx;
  int wholeY = (int)sy;
  int fractionY = dy / 2;
  // To handle direction of line
  dx = dx * dir;

  // Simple gradient plot, y whole value alternates 1 pixel above and 1 pixel
  // below until y fraction is bigger than x difference The maths makes sense
  while (x != ex) {
    fb->plotPixel(x, wholeY, 1.0f, 1.0f, 1.0f);
    fractionY += dy;
    if (fractionY >= dx) {
      wholeY += 1;
      fractionY -= dx;
    } else if (fractionY <= dx) {
      wholeY -= 1;
      fractionY += dx;
    }
    x += dir;
  }
  return 0;
}

int draw_y_line(FrameBuffer *fb, int sx, int sy, int ex, int ey) {
  int dir = 1;
  if (sy > ey) {
    dir = -1;
  }
  int dy = ey - sy;
  int dx = ex - sx;
  int y = sy;
  int wholeX = (int)sx;
  int fractionX = dx / 2;
  // To handle direction of line
  dy = dy * dir;

  // Simple gradient plot, x whole value alternates 1 pixel left and 1 pixel
  // right until x fraction is bigger than y difference The maths makes sense
  while (y != ey) {
    fb->plotPixel(wholeX, y, 1.0f, 1.0f, 1.0f);
    fractionX += dx;
    if (fractionX >= dy) {
      wholeX += 1;
      fractionX -= dy;
    } else if (fractionX <= dy) {
      wholeX -= 1;
      fractionX += dy;
    }
    y += dir;
  }
  return 0;
}

int draw_line(FrameBuffer *fb, int sx, int sy, int ex, int ey) {
  if ((sx == ex) && (sy == ey)) {
    // Plot one pixel
    return fb->plotPixel(sx, sy, 1.0f, 1.0f, 1.0f);

  } else if (((ex - sx) * (ex - sx)) >= ((ey - sy) * (ey - sy))) {
    // If gradient is less than 1 draw x line
    return draw_x_line(fb, sx, sy, ex, ey);

  } else {
    // If gradient is 1 or more, draw y line.
    return draw_y_line(fb, sx, sy, ex, ey);
  }
}
