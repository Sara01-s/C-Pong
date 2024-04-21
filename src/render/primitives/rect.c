#include "rect.h"

unsigned long long max_vertices_memory = 0;

void rect_set_max_vertices_memory(unsigned long long max_vertices) {
    max_vertices_memory = max_vertices;
}

Rect* rect_create(GLuint shader) {

    Rect* rect = malloc(sizeof(Rect));

    GLuint rect_indices_draw_order[] = {
        0, 1, 2,
        2, 3, 0,
    };

    /* Rect settings */
    GLuint vao_rect = vao_create(true);
    GLuint vb_rect = vb_create(NULL, max_vertices_memory * sizeof(Vertex), true); /* NULL data because we want to modify it in runtime */
    GLuint ib_rect_length = sizeof(rect_indices_draw_order) / sizeof(rect_indices_draw_order[0]);
    GLuint ib_rect = ib_create(rect_indices_draw_order, ib_rect_length, true);

    /* attrib pointer args: location (used in shaders), number of things, type of the things, normalized?, size of each vertex, offset of the property inside the vertex (starting at 0) */
    vao_add_attrib(GL_FLOAT, 2, sizeof(Vertex), (void*) offsetof(Vertex, position));
    vao_add_attrib(GL_FLOAT, 4, sizeof(Vertex), (void*) offsetof(Vertex, color));
    vao_add_attrib(GL_FLOAT, 2, sizeof(Vertex), (void*) offsetof(Vertex, texcoords));

    rect->vao_id = vao_rect;
    rect->vb_id = vb_rect;
    rect->ib_id = ib_rect;
    rect->shader = shader;

    return rect;
}

void rect_dispose(Rect* rect) {
    vao_dispose(rect->vao_id);
    vb_dispose(rect->vb_id);
    ib_dispose(rect->ib_id);
    shader_dispose(rect->shader);

    free(rect);
}