#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "../utils.h"

GLuint vao_create(bool auto_bind);
void vao_bind(GLuint vao_id);
void vao_unbind(GLuint vao_id);
void vao_add_attrib(GLenum element_type, GLint element_count, GLsizei stride, const void* pointer);
void vao_dispose(GLuint vao_id);

#endif /* VERTEXARRAY_H */