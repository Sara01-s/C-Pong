#ifndef UTILS_H
#define UTILS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

/* to better represent vector, colors, texcoords element access */
#define X 0
#define Y 1
#define Z 2
#define W 3
#define R X
#define G Y
#define B Z
#define A W
#define U X
#define V Y

#define log_info(message) printf("[INFO] %s\n", message)
#define log_error(message) printf("[ERROR] %s\n", message)

/* use for debugging OpenGL errors, comment if not used */
#define DEBUG_OPENGL
//#define NDEBUG

#ifdef DEBUG_OPENGL
#   define GL_CALL(expression) while (glGetError() != GL_NO_ERROR);\
                                expression;\
                                assert(GLLogCall(#expression, __FILE__, __LINE__))
#else
#   define GL_CALL(expression) expression
#endif

bool GLLogCall(const char* function_name, const char* file, int line);

const char* read_file(const char* filepath);

#endif // UTILS_H