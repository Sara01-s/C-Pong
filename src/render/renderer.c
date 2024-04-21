#include "renderer.h"

bool gl_initialized = false;

GLFWwindow* renderer_window_create(unsigned long long max_memory) {
    GLFWwindow* window;

    if (!glfwInit()) {
        log_error("Failed to initialize GLFW\n");
        assert(false);
    }

    window = glfwCreateWindow(1280, 720, "OpongGL", NULL, NULL);

    if (!window) {
        log_error("Failed to create GLFW Window\n");
        glfwTerminate();
        assert(false);
    }

    glfwSwapInterval(1);    /* 1 means VSync */
    glfwMakeContextCurrent(window);
    int screen_width = 0;
    int screen_height = 0;
    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), NULL, NULL, &screen_width, &screen_height);
    glfwSetWindowPos(window, screen_width / 6, screen_height / 6);

    if (glewInit() != GLEW_OK) {
        log_error("Failed to initialize GLEW\n");
        glfwTerminate();
        assert(false);
    }

    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    rect_set_max_vertices_memory(max_memory);

    gl_initialized = true;
    return window;
}

void renderer_set_clearcolor(float r, float g, float b, float a) {
    if (!gl_initialized) {
        log_error("Call renderer_window_create before setting a clear color!");
        return;
    }

    GL_CALL(glClearColor(r, g, b, a));
}

void renderer_clear_screen() {
    if (!gl_initialized) {
        log_error("Call renderer_window_create before setting a clearing the screen!");
        return;
    }

    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}

void renderer_config_mvp_matrix(mat4* mvp) {
    mat4 model_matrix;
    glm_mat4_identity(model_matrix);

    mat4 view_matrix;
    glm_mat4_identity(view_matrix);

    mat4 projection_matrix;
    glm_mat4_identity(projection_matrix);
    glm_ortho(-16.0f, 16.0f, -9.0f, 9.0f, -10.0f, 10.0f, projection_matrix);

    glm_mat4_mul(model_matrix, view_matrix, mvp[0]);
    glm_mat4_mul(mvp[0], projection_matrix, mvp[0]);
}

void renderer_draw_entity(Entity* entity, mat4 mvp_matrix) {
    Vertex* rect_verts = vertex_rect_create (
        entity->position, 
        entity->scale,
        entity->color
    );

    Vertex rect[4];
    memcpy(rect, rect_verts, RECT_VERTICES * sizeof(Vertex));

    free(rect_verts);

    vao_bind(entity->rect->vao_id);
    vb_bind(entity->rect->vb_id);
    vb_set_sub_data(rect, sizeof(rect));
    shader_bind(entity->rect->shader);
    shader_set_uniform_mat4(entity->rect->shader, "u_MVP", mvp_matrix);

    GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}
