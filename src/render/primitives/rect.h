#ifndef RECT_H
#define RECT_H


#include "../../utils.h"

#include "../vertexarray.h"
#include "../vertexbuffer.h"
#include "../indexbuffer.h"
#include "../shader.h"

typedef struct rect {
    GLuint vao_id;
    GLuint vb_id;
    GLuint ib_id;
    GLuint shader;
} Rect;

void rect_set_max_vertices_memory(unsigned long long max_vertices);
Rect* rect_create(GLuint shader);
void rect_dispose(Rect* rect);

#endif /* RECT_H */