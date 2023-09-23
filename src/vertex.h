#ifndef VERTEX_H
#define VERTEX_H

#include <CGLM/glm/vec2.h>
#include <CGLM/glm/vec4.h>

#define SQUARE_VERTICES 4

typedef struct {
    vec2 position;
    vec4 color;
    vec2 texcoords;
} Vertex;


void vertex_set_position(Vertex* vertex, vec2 position);
void vertex_set_color(Vertex* vertex, vec4 color);
void vertex_set_texcoords(Vertex* vertex, vec2 texcoords);
void vertex_create(Vertex* vertex, vec2 position, vec4 color, vec2 texcoords);
Vertex* vertex_square_create(vec2 origin_position, vec2 scale, vec4 color);

#endif /* VERTEX_H */