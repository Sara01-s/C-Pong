#include "shader.h"
#include <stdlib.h>
#include <stdio.h>

GLuint shader_create(GLenum shader_type, const char* source) {

    GL_CALL(GLuint shader_program = glCreateShader(shader_type));
    GL_CALL(glShaderSource(shader_program, 1, &source, NULL)); // OpenGL will use strlen under the hood to determine the src size
    GL_CALL(glCompileShader(shader_program));

    GLint shader_compile_status = 0;
    GL_CALL(glGetShaderiv(shader_program, GL_COMPILE_STATUS, &shader_compile_status));

    if (shader_compile_status == GL_FALSE) {
        GLsizei log_length = 0;
        GL_CALL(glGetShaderiv(shader_program, GL_INFO_LOG_LENGTH, &log_length));
        GLchar* log_message = (char*) malloc(log_length * sizeof(GLchar));

        GL_CALL(glGetShaderInfoLog(shader_program, log_length, &log_length, log_message));
        log_info(log_message);
    }
    
    return shader_program;
}

GLuint shader_compile(GLuint vert_shader, GLuint frag_shader) {

    GL_CALL(GLuint shader_program = glCreateProgram());

    GL_CALL(glAttachShader(shader_program, vert_shader));
    GL_CALL(glAttachShader(shader_program, frag_shader));
    GL_CALL(glLinkProgram(shader_program));

    GLint shader_link_status = 0;
    GL_CALL(glGetProgramiv(shader_program, GL_LINK_STATUS, &shader_link_status));

    if (shader_link_status == GL_FALSE) {
        GLsizei log_length = 0;
        GL_CALL(glGetShaderiv(shader_program, GL_INFO_LOG_LENGTH, &log_length));
        GLchar* log_message = (char*) malloc(log_length * sizeof(GLchar));

        GL_CALL(glGetProgramInfoLog(shader_program, log_length, &log_length, log_message));
        log_info(log_message);
    }

    return shader_program;
}

void shader_set_uniform_int(GLuint shader_id, const char* property_name, int value) {
    GLint property_location = shader_get_uniform_loc(shader_id, property_name);
    GL_CALL(glUniform1i(property_location, value));
}

void shader_set_uniform_float(GLuint shader_id, const char* property_name, float value) {
    GLint property_location = shader_get_uniform_loc(shader_id, property_name);
    GL_CALL(glUniform1f(property_location, value));
}

void shader_set_uniform_mat4(GLuint shader_id, const char* property_name, mat4 matrix) {
    GLint property_location = shader_get_uniform_loc(shader_id, property_name);
    glUniformMatrix4fv(property_location, 1, GL_FALSE, &matrix[0][0]);
}

void shader_set_uniform_vec3(GLuint shader_id, const char* property_name, vec3 vector) {
    GLfloat v_x = *(&vector[0]);
    GLfloat v_y = *(&vector[1]);
    GLfloat v_z = *(&vector[2]);
    GLint property_location = shader_get_uniform_loc(shader_id, property_name);
    GL_CALL(glUniform3f(property_location, v_x, v_y, v_z));
}

void shader_set_uniform_vec4(GLuint shader_id, const char* property_name, vec4 vector) {
    GLfloat v_x = *(&vector[0]);
    GLfloat v_y = *(&vector[1]);
    GLfloat v_z = *(&vector[2]);
    GLfloat v_w = *(&vector[3]);
    GLint property_location = shader_get_uniform_loc(shader_id, property_name);
    GL_CALL(glUniform4f(property_location, v_x, v_y, v_z, v_w));
}

GLint shader_get_uniform_loc(GLuint shader_id, const char* property_name) {
    GL_CALL(GLint location = glGetUniformLocation(shader_id, property_name));
    return location;
}
