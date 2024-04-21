#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "../utils.h"

GLuint ib_create(const GLuint* data, GLuint indices_count, bool auto_bind);
void ib_bind(GLuint ib_id);
void ib_dispose(GLuint ib_id);


#endif /* INDEXBUFFER_H */