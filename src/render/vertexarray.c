#include "vertexarray.h"

void vao_bind(GLuint vao_id) {
    GL_CALL(glBindVertexArray(vao_id));
}

void vao_unbind(GLuint vao_id) {
    GL_CALL(glBindVertexArray(0));
}

GLuint vao_create(bool auto_bind) {
    GLuint vao_id;
    GL_CALL(glGenVertexArrays(1, &vao_id));

    if (auto_bind) {
        vao_bind(vao_id);
    }

    return vao_id;
}

void vao_dispose(GLuint vao_id) {
    GL_CALL(glDeleteVertexArrays(1, &vao_id));
}


