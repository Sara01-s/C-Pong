#include <stdlib.h>
#include "indexbuffer.h"

void ib_bind(GLuint ib_id) {
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_id));
}

void ib_unbind(GLuint ib_id) {
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

GLuint ib_create(const GLuint* data, GLuint count, bool auto_bind) {
    GLuint ib_id;
    GL_CALL(glGenBuffers(1, &ib_id));
    ib_bind(ib_id);
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_DYNAMIC_DRAW));

    if (!auto_bind) {
        ib_unbind(ib_id);
    }

    return ib_id;
}

void ib_dispose(GLuint ib_id) {
    GL_CALL(glDeleteBuffers(1, &ib_id));
}
