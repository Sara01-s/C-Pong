#ifndef SHADER_H
#define SHADER_H

#include "../utils.h"
#include <CGLM/include/cglm/mat4.h>
#include <CGLM/include/cglm/vec3.h>
#include <CGLM/include/cglm/vec4.h>

GLuint shader_create(GLenum shader_type, const char* source);
GLuint shader_create_from_file(const char* vsh_filepath, const char* fsh_filepath);
GLuint shader_compile(GLuint vert_shader, GLuint frag_shader);

void   shader_bind(GLuint shader_id);
void   shader_set_uniform_int(GLuint shader_id, const char* property_name, int value);
void   shader_set_uniform_float(GLuint shader_id, const char* property_name, float value);
void   shader_set_uniform_mat4(GLuint shader_id, const char* property_name, mat4 matrix);
void   shader_set_uniform_vec3(GLuint shader_id, const char* property_name, vec3 vector);
void   shader_set_uniform_vec4(GLuint shader_id, const char* property_name, vec4 vector);

GLint  shader_get_uniform_loc(GLuint shader_id, const char* property_name);
void   shader_dispose(GLuint shader_id);

#endif /* SHADER_H */