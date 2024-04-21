#include "vertexbuffer.h"

void vb_bind(GLuint vb_id) {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vb_id));
}

void vb_unbind(GLuint vb_id) {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

GLuint vb_create(const void* data, GLsizeiptr size, bool auto_bind) {
    GLuint vb_id;
    GL_CALL(glGenBuffers(1, &vb_id));
    vb_bind(vb_id);
    /* A dynamic buffer data is a read-write buffer data */
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));

    if (!auto_bind) {
        vb_unbind(vb_id);
    }

    return vb_id;
}

/* Sets bound vertex buffer sub data */
void vb_set_sub_data(const void* sub_data, GLsizeiptr size) {
    GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0x0, size, sub_data));
}

void vb_dispose(GLuint vb_id) {
    GL_CALL(glDeleteBuffers(1, &vb_id));
}

void vertex_set_position(Vertex* vertex, vec2 position) {
    glm_vec2_copy(position, vertex->position);
}

void vertex_set_color(Vertex* vertex, vec4 color) {
    glm_vec4_copy(color, vertex->color);
}

void vertex_set_texcoords(Vertex* vertex, vec2 texcoords) {
    glm_vec2_copy(texcoords, vertex->texcoords);
}

void vertex_configure(Vertex* vertex, vec2 position, vec4 color, vec2 texcoords) {
    vertex_set_position(vertex, position);
    vertex_set_color(vertex, color);
    vertex_set_texcoords(vertex, texcoords);
}

/* Don't forget to free() the created rect vertices */
Vertex* vertex_rect_create(vec2 origin_position, vec2 scale, vec4 color) {

    Vertex* rect_vertices = malloc(RECT_VERTICES * sizeof(Vertex));

    assert(rect_vertices != NULL);

    vertex_set_color(&rect_vertices[0], color);
    vertex_set_color(&rect_vertices[1], color);
    vertex_set_color(&rect_vertices[2], color);
    vertex_set_color(&rect_vertices[3], color);

    vertex_set_texcoords(&rect_vertices[0], (vec2) { 0.0f, 0.0f });
    vertex_set_texcoords(&rect_vertices[1], (vec2) { 1.0f, 0.0f });
    vertex_set_texcoords(&rect_vertices[2], (vec2) { 1.0f, 1.0f });
    vertex_set_texcoords(&rect_vertices[3], (vec2) { 0.0f, 1.0f });

    vertex_set_position(&rect_vertices[0], (vec2) { origin_position[X],            origin_position[Y]            });
    vertex_set_position(&rect_vertices[1], (vec2) { origin_position[X] + scale[X], origin_position[Y]            });
    vertex_set_position(&rect_vertices[2], (vec2) { origin_position[X] + scale[X], origin_position[Y] + scale[Y] });
    vertex_set_position(&rect_vertices[3], (vec2) { origin_position[X],            origin_position[Y] + scale[Y] });
    
    return rect_vertices;
}