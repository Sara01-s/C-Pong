#ifndef RENDERER_H
#define RENDERER_H

#include "../utils.h"

#include "vertexarray.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "shader.h"

void renderer_set_clearcolor(float r, float g, float b, float a);
void renderer_clear_screen();

#endif /* RENDERER_H */