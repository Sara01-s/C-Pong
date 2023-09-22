#include <GL/glew.h>
#include <stdio.h>
#include <CGLM/glm/cam.h>
#include <CGLM/glm/struct.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"
#include "shader.h"

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(void) {
    
    log_info("Running game...");

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1280, 720, "Mi primer jueguito en C", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1);    /* 1 means VSync */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    /* Vertex buffer data */
    float vertices[] = {
        /* square 1 vertices (counter clock-wise)*/
        -14.0f,  4.0f, /* index 0 */
        -13.0f,  4.0f, /* index 1 */
        -13.0f,  8.0f, /* index 2 */
        -14.0f,  8.0f, /* index 3 */

        /* square 2 vertices (counter clock-wise)*/
         12.0f, -8.0f, /* index 4 */
         13.0f, -8.0f, /* index 5 */
         13.0f, -4.0f, /* index 6 */
         12.0f, -4.0f  /* index 7 */
    };

    GLuint indices_draw_order[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4
    };

    GLuint vertex_array_object;
    GL_CALL(glGenVertexArrays(1, &vertex_array_object));
    GL_CALL(glBindVertexArray(vertex_array_object));

    GLuint vertex_buffer_object;
    GL_CALL(glGenBuffers(1, &vertex_buffer_object));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW));

    GLuint vertex_index_buffer;
    GL_CALL(glGenBuffers(1, &vertex_index_buffer));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_index_buffer));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_draw_order), indices_draw_order, GL_DYNAMIC_DRAW));

    /* location 0 , and it's a vec2 so we input 2 */
    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0x0));
    GL_CALL(glEnableVertexAttribArray(0));

    const char* vertex_src = read_file("assets/vsh_default.glsl");
    const char* fragmt_src = read_file("assets/fsh_default.glsl");
    GLuint vertex_shader   = shader_create(GL_VERTEX_SHADER, vertex_src);
    GLuint fragment_shader = shader_create(GL_FRAGMENT_SHADER, fragmt_src);

    GLuint shader = shader_compile(vertex_shader, fragment_shader);

    GL_CALL(glUseProgram(shader));

    mat4 projection_matrix;
    glm_mat4_identity(projection_matrix);
    glm_ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f, projection_matrix);

    GL_CALL(glClearColor(0.2f, 0.3f, 0.8f, 1.0f));

    shader_set_uniform_mat4(shader, "_MVP", projection_matrix);

    /* Game loop */
    while (!glfwWindowShouldClose(window)) {

        process_input(window);

        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

        GL_CALL(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0x0));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    log_info("Game closed, Bye bye.");

    free((void*) vertex_src);
    free((void*) fragmt_src);
    return 0;
}
