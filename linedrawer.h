#ifndef _linedrawer_h_
#define _linedrawer_h_

#include "framebuffer.h"
// sx - starting x value
// sy - starting y value
// ex - end x value
// ey - end y value
int draw_line(FrameBuffer *fb, int sx, int sy, int ex, int ey);

#endif
