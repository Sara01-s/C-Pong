#ifndef BUFFERLAYOUT_H
#define BUFFERLAYOUT_H

#include <assert.h>
#include "../utils.h"

typedef struct vertex_buffer_element {
    GLuint type;
    GLuint count;
    GLchar is_normalized;
} VertexBufferElement;

inline GLuint bufferlayout_get_sizeoftype(GLuint type) {
    switch (type) {
        case GL_FLOAT         : return sizeof(GLfloat);
        case GL_UNSIGNED_INT  : return sizeof(GLuint);
        case GL_UNSIGNED_BYTE : return sizeof(GLubyte);
    }

    log_error("Fatal: Failed to get size of buffer layout");
    assert(false);
    return 0;
}

#endif /* BUFFERLAYOUT_H */