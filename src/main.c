#include <GL/glew.h>
#include <stdio.h>
#include <CGLM/glm/cam.h>
#include <CGLM/glm/struct.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"
#include "shader.h"
#include "vertex.h"

const unsigned long long MAX_VERTICES = 1024ULL; /* 1 kilo byte */


void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(void) {

    log_info("Running game...");

    /* Graphics initialization */
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
    
    
    /* Static Data*/
    float circle_vertices[] = {
       /* Pos */ -0.5f, -0.5f, /* TexCoords */  0.0f,  0.0f, /* index 0 */
       /* Pos */  0.5f, -0.5f, /* TexCoords */  0.0f,  1.0f, /* index 1 */
       /* Pos */  0.5f,  0.5f, /* TexCoords */  1.0f,  1.0f, /* index 2 */
       /* Pos */ -0.5f,  0.5f, /* TexCoords */  0.0f,  1.0f  /* index 3 */
    };

    GLuint square_indices_draw_order[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4
    };

    GLuint circle_indices_draw_order[] = {
        0, 1, 2,
        2, 3, 0
    };

    /* Squares settings */
    GLuint square_vertex_array;
    GL_CALL(glGenVertexArrays(1, &square_vertex_array));
    GL_CALL(glBindVertexArray(square_vertex_array));

    GLuint squares_vertex_buffer;
    GL_CALL(glGenBuffers(1, &squares_vertex_buffer));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, squares_vertex_buffer));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW)); /* A dynamic buffer data is a read-write buffer data */

    GLuint squares_index_buffer;
    GL_CALL(glGenBuffers(1, &squares_index_buffer));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squares_index_buffer));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices_draw_order), square_indices_draw_order, GL_DYNAMIC_DRAW));

    /* attrib pointer args: location, number of things, type of the things, normalied?, size of each vertex, offset of the property inside the vertex (starting at 0) */
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position)));

    /* Circle settings */
    GLuint circle_vertex_array;
    GL_CALL(glGenVertexArrays(1, &circle_vertex_array));
    GL_CALL(glBindVertexArray(circle_vertex_array));

    GLuint circle_vertex_buffer;
    GL_CALL(glGenBuffers(1, &circle_vertex_buffer));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, circle_vertex_buffer));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(circle_vertices), circle_vertices, GL_DYNAMIC_DRAW));

    GLuint circle_index_buffer;
    GL_CALL(glGenBuffers(1, &circle_index_buffer));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, circle_index_buffer));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(circle_indices_draw_order), circle_indices_draw_order, GL_DYNAMIC_DRAW));

    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0)); /* Positions */
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 8)); /* Tex Coords */

    /* Shaders setup */
    const char* squares_vertex_src = read_file("assets/vsh_square.glsl");
    const char* squares_fragmt_src = read_file("assets/fsh_square.glsl");
    const char* circle_vertex_src = read_file("assets/vsh_circle.glsl");
    const char* circle_fragmt_src = read_file("assets/fsh_circle.glsl");
    GLuint squares_vertex_shader = shader_create(GL_VERTEX_SHADER, squares_vertex_src);
    GLuint squares_fragmt_shader = shader_create(GL_FRAGMENT_SHADER, squares_fragmt_src);
    GLuint circle_vertex_shader = shader_create(GL_VERTEX_SHADER, circle_vertex_src);
    GLuint cirlce_fragmt_shader = shader_create(GL_FRAGMENT_SHADER, circle_fragmt_src);

    GLuint squares_shader = shader_compile(squares_vertex_shader, squares_fragmt_shader);
    GLuint circle_shader = shader_compile(circle_vertex_shader, cirlce_fragmt_shader);

    /* Space Setup */
    mat4 model_matrix;
    glm_mat4_identity(model_matrix);

    mat4 view_matrix;
    glm_mat4_identity(view_matrix);

    mat4 model_view_matrix;
    glm_mat4_identity(model_view_matrix);

    mat4 projection_matrix;
    glm_mat4_identity(projection_matrix);
    glm_ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f, projection_matrix);

    mat4 mvp_matrix;
    glm_mat4_mul(model_matrix, view_matrix, model_view_matrix);
    glm_mat4_mul(model_view_matrix, projection_matrix, mvp_matrix);

    GL_CALL(glClearColor(0.2f, 0.3f, 0.8f, 1.0f));
    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    /* Game loop */
    while (!glfwWindowShouldClose(window)) {

        process_input(window);

        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

        /* Dinamically set vertex buffer data */
        Vertex* square_verts_player_1 = vertex_square_create((vec2) { -14.0f, 0.0f }, 1.0);
        Vertex* square_verts_player_2 = vertex_square_create((vec2) {  13.0f, 0.0f }, 1.0);
        Vertex all_squares_vertices[8];

        memcpy(all_squares_vertices, square_verts_player_1, 4 * sizeof(Vertex));
        memcpy(all_squares_vertices + 4, square_verts_player_2, 4 * sizeof(Vertex));

        free(square_verts_player_1);
        free(square_verts_player_2);

        GL_CALL(glBindVertexArray(square_vertex_array));
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, squares_vertex_buffer));
        GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0x0, sizeof(all_squares_vertices), all_squares_vertices));
        GL_CALL(glUseProgram(squares_shader));
        shader_set_uniform_mat4(squares_shader, "u_MVP", mvp_matrix);
        GL_CALL(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0));

        GL_CALL(glBindVertexArray(circle_vertex_array));
        GL_CALL(glUseProgram(circle_shader));
        shader_set_uniform_mat4(circle_shader, "u_MVP", mvp_matrix);
        GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    free((void*) squares_vertex_src);
    free((void*) squares_fragmt_src);

    log_info("Game closed, Bye bye.");
    return 0;
}
