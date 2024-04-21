#include "vertexarray.h"

GLuint current_index = 0;

void vao_bind(GLuint vao_id) {
    GL_CALL(glBindVertexArray(vao_id));
    current_index = 0;
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

void vao_add_attrib(GLenum element_type, GLint element_count, GLsizei stride, const void* pointer) {
    GL_CALL(glEnableVertexAttribArray(current_index));
    GL_CALL(glVertexAttribPointer(current_index, element_count, GL_FLOAT, GL_FALSE, stride, pointer));
    current_index++;
}

void vao_dispose(GLuint vao_id) {
    GL_CALL(glDeleteVertexArrays(1, &vao_id));
}


