#ifndef VERTEX_H
#define VERTEX_H

#include <CGLM/glm/vec4.h>

typedef struct {
    vec2 position;
    vec3 color;
    vec2 texcoords;
} Vertex;


void vertex_set_position(Vertex* vertex, vec2 position);
void vertex_set_color(Vertex* vertex, vec4 color);
void vertex_set_texcoords(Vertex* vertex, vec2 texcoords);
void vertex_create(Vertex* vertex, vec2 position, vec4 color, vec2 texcoords);
Vertex* vertex_square_create(vec2 origin_position, float size);

#endif /* VERTEX_H */