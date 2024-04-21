#ifndef RENDERER_H
#define RENDERER_H

#include <CGLM/include/cglm/struct.h>
#include <CGLM/include/cglm/cam.h>
#include <CGLM/include/cglm/io.h>

#include <string.h>

#include "../utils.h"
#include "../game/entity.h"

#include "vertexarray.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "shader.h"

GLFWwindow* renderer_window_create(unsigned long long max_memory);
void renderer_set_clearcolor(float r, float g, float b, float a);
void renderer_clear_screen();
void renderer_config_mvp_matrix(mat4* mvp);

void renderer_draw_entity(Entity* entity, mat4 mvp_matrix);

#endif /* RENDERER_H */