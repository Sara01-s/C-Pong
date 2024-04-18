#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <CGLM/include/cglm/vec4.h>
#include <CGLM/include/cglm/vec2.h>
#include "../utils.h"

#define SQUARE_VERTICES 4

typedef struct {
    vec2 position;
    vec4 color;
    vec2 texcoords;
} Vertex;

GLuint vb_create(const void* data, GLuint size, bool auto_bind);
void vb_set_data(const void* data, GLuint size);
void vb_bind(GLuint vb_id);
void vb_unbind(GLuint vb_id);
void vb_dispose(GLuint vb_id);

void vertex_set_position(Vertex* vertex, vec2 position);
void vertex_set_color(Vertex* vertex, vec4 color);
void vertex_set_texcoords(Vertex* vertex, vec2 texcoords);
void vertex_configure(Vertex* vertex, vec2 position, vec4 color, vec2 texcoords);
Vertex* vertex_square_create(vec2 origin_position, vec2 scale, vec4 color);

#endif /* VERTEXBUFFER_H */