#include <CGLM/include/cglm/struct.h>
#include <CGLM/include/cglm/cam.h>
#include <CGLM/include/cglm/io.h>
#include <string.h>

#include "utils.h"
#include "render/renderer.h"
#include "game/input.h"
#include "game/node.h"
#include "game/collider.h"

const unsigned long long MAX_VERTICES = 1024ULL; /* 1kb */

float player_1_speed = 20.0f;
float player_2_speed = 20.0f;

vec2  ball_direction = { 1.0f, 0.0f };
float ball_speed     = 10.0f;

int main(void) {

    log_info("Creating nodes...");

    Node* player_1 = node_create (
        (vec2) { -14.0f, 0.0f },
        (vec2) { 0.8f, 4.0f },
        collider_create((vec2) { -14.0f, 0.0f }, (vec2) { 0.8f, 4.0f }),
        (vec2) { 0.0f, 0.0f },
        (vec4) { 0.5412f, 0.3059f, 0.7922f, 1.0f }
    );

    Node* player_2 = node_create (
        (vec2) { 13.0f, 0.0f },
        (vec2) { 0.8f, 4.0f },
        collider_create((vec2) { 13.0f, 0.0f }, (vec2) { 0.8f, 4.0f }),
        (vec2) { 0.0f, 0.0f },
        (vec4) { 0.5412f, 0.3059f, 0.7922f, 1.0f }
    );

    Node* ball = node_create (
        (vec2) { 0.0f, 0.0f },
        (vec2) { 1.0f, 1.0f },
        collider_create((vec2) { 0.0f, 0.0f }, (vec2) { 1.0f, 1.0f }),
        (vec2) { 0.0f, 0.0f },
        (vec4) { 0.7725f, 0.1490f, 0.4705f, 1.0f }
    );

    log_info("Initializing graphics...");

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
    int screen_width = 0;
    int screen_height = 0;
    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), NULL, NULL, &screen_width, &screen_height);
    glfwSetWindowPos(window, screen_width / 6, screen_height / 6);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    renderer_set_clearcolor(0.0667f, 0.0f, 0.0902f, 1.0f);
    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


    /* Squares and colliders settings */
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

    GLuint vao_squares = vao_create(true);
    GLuint vb_squares = vb_create(0x0, MAX_VERTICES * sizeof(Vertex), true); /* 0x0 in data because we want to modify it in runtime */
    GLuint ib_squares = ib_create(square_indices_draw_order, 1, true);

    /* attrib pointer args: location (used in shaders), number of things, type of the things, normalized?, size of each vertex, offset of the property inside the vertex (starting at 0) */
    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position)));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, color)));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texcoords)));
    GL_CALL(glEnableVertexAttribArray(2));

    /* Circle settings */
    GLuint vao_circle = vao_create(true);
    GLuint vb_circle = vb_create(0x0, MAX_VERTICES * sizeof(Vertex), true);
    GLuint ib_circle = ib_create(circle_indices_draw_order, 1, true);

    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position)));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, color)));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texcoords)));
    GL_CALL(glEnableVertexAttribArray(2));

    /* Shaders setup */
    GLuint squares_shader = shader_create_from_file("assets/vsh_square.glsl", "assets/fsh_square.glsl");
    GLuint circle_shader = shader_create_from_file("assets/vsh_circle.glsl", "assets/fsh_circle.glsl");

    /* Space Setup */ 
    mat4 model_matrix;
    glm_mat4_identity(model_matrix);

    mat4 view_matrix;
    glm_mat4_identity(view_matrix);

    mat4 projection_matrix;
    glm_mat4_identity(projection_matrix);
    glm_ortho(-16.0f, 16.0f, -9.0f, 9.0f, -10.0f, 10.0f, projection_matrix);

    mat4 mvp_matrix;
    glm_mat4_mul(model_matrix, view_matrix, mvp_matrix);
    glm_mat4_mul(mvp_matrix, projection_matrix, mvp_matrix);
    double current_frame_time = glfwGetTime();
    double delta_time         = 0.0;
    double last_frame_time    = 0.0;

    log_info("Running game...");

    /* Game loop */
    while (!glfwWindowShouldClose(window)) {
        
        input_check_quit(window);
        renderer_clear_screen();

        /* Time update */
        current_frame_time  = glfwGetTime();
        delta_time          = current_frame_time - last_frame_time;
        last_frame_time     = current_frame_time;

        /* Players */
        float p1_vertical_axis = input_get_vertical(window, P1);
        player_1->position[1] += p1_vertical_axis * player_1_speed * delta_time;

        float p2_vertical_axis = input_get_vertical(window, P2);
        player_2->position[1] += p2_vertical_axis * player_2_speed * delta_time;

        /* Dinamically set square vertices buffer data */
        Vertex* square_verts_player_1 = vertex_square_create (
            player_1->position, 
            player_1->scale,
            player_1->color
        );

        Vertex* square_verts_player_2 = vertex_square_create (
            player_2->position, 
            player_2->scale,
            player_2->color
        );

        Vertex all_squares_vertices[8];

        memcpy(all_squares_vertices, square_verts_player_1, SQUARE_VERTICES * sizeof(Vertex));
        memcpy(all_squares_vertices + SQUARE_VERTICES, square_verts_player_2, SQUARE_VERTICES * sizeof(Vertex));

        free(square_verts_player_1);
        free(square_verts_player_2);

        vao_bind(vao_squares);
        vb_bind(vb_squares);
        vb_set_sub_data(all_squares_vertices, sizeof(all_squares_vertices));
        shader_bind(squares_shader);
        shader_set_uniform_mat4(squares_shader, "u_MVP", mvp_matrix);
        GL_CALL(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0));


        /* Ball */
        glm_vec2_scale(ball_direction, ball_speed * delta_time, ball->velocity);
        glm_vec2_add(ball->position, ball->velocity, ball->position);

        Vertex* circle_verts = vertex_square_create (
            ball->position, 
            ball->scale,
            ball->color
        );

        Vertex circle_square[4];
        memcpy(circle_square, circle_verts, SQUARE_VERTICES * sizeof(Vertex));

        free(circle_verts);

        vao_bind(vao_circle);
        vb_bind(vb_circle);
        vb_set_sub_data(circle_square, sizeof(circle_square));
        shader_bind(circle_shader);
        shader_set_uniform_mat4(circle_shader, "u_MVP", mvp_matrix);
        GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    vao_dispose(vao_squares);
    vao_dispose(vao_circle);
    vb_dispose(vb_squares);
    vb_dispose(vb_circle);
    ib_dispose(ib_squares);
    ib_dispose(ib_circle);

    node_dispose(player_1);
    node_dispose(player_2);

    free(ball);

    printf("%s", "\n");
    log_info("Game closed, Bye bye.");
    return 0;
}
