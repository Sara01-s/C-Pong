#include <CGLM/include/cglm/struct.h>

#include "render/renderer.h"
#include "game/input.h"

const unsigned long long MAX_GAME_VERTICES = 1024ULL; /* 1kb */
const float MAX_BOUNCE_ANGLE_RAD = 5.0F * M_PI / 12.0F; /* 75 degrees */

float player_1_speed = 100.0f;
float player_2_speed = 100.0f;

vec2  ball_direction = { 1.0f, 0.0f };
float ball_speed     = 10.0f;

void ball_paddle_bounce(Entity* ball, Entity* paddle) {
    /* src: https://gamedev.stackexchange.com/questions/4253/in-pong-how-do-you-calculate-the-balls-direction-when-it-bounces-off-the-paddl */
    float ball_displacement = paddle->position[Y] + (paddle->scale[Y] / 2.0f) - ball->position[Y];
    float normalized_displacement = ball_displacement / (paddle->scale[Y] / 2.0f);
    float bounce_angle = normalized_displacement * MAX_BOUNCE_ANGLE_RAD;

    float ball_dir_x = ball_speed *  cos(bounce_angle);
    float ball_dir_y = ball_speed * -sin(bounce_angle);

    ball_dir_x *= ball_direction[X] < 0.0f ? 1.0f : -1.0f;

    ball_direction[X] = ball_dir_x;
    ball_direction[Y] = ball_dir_y;

    glm_vec2_normalize(ball_direction);
}

void ball_top_wall_bounce(Entity* ball, Entity* wall) {
    ball_direction[Y] = -1;
}

void ball_bot_wall_bounce(Entity* ball, Entity* wall) {
    ball_direction[Y] = 1;
}

void ball_left_wall_bounce(Entity* ball, Entity* wall) {
    entity_set_position(ball, (vec2) { 0.0f, 0.0f });
    ball_direction[X] = 1.0f;
    ball_direction[Y] = 0.0f;
    log_info("left point");
}

void ball_right_wall_bounce(Entity* ball, Entity* wall) {
    entity_set_position(ball, (vec2) { 0.0f, 0.0f });
    ball_direction[X] = -1.0f;
    ball_direction[Y] = 0.0f;
    log_info("right point");
}

int main(void) {

    /* Graphics initialization */
    log_info("Initializing graphics...");

    GLFWwindow* window = renderer_window_create(MAX_GAME_VERTICES);
    renderer_set_clearcolor(0.0667f, 0.0f, 0.0902f, 1.0f);

    /* Entities initialization */
    log_info("Creating entities...");

    Entity* player_1 = entity_create (
        (vec2) { -14.0f, 0.0f },
        (vec2) { 0.8f, 4.0f },
        (vec2) { 0.0f, 0.0f },
        (vec4) { 0.5412f, 0.3059f, 0.7922f, 1.0f }
    );
        
    Entity* player_2 = entity_create (
        (vec2) { 13.0f, 0.0f },
        (vec2) { 0.8f, 4.0f },
        (vec2) { 0.0f, 0.0f },
        (vec4) { 0.5412f, 0.3059f, 0.7922f, 1.0f }
    );

    Entity* ball = entity_create (
        (vec2) { 0.0f, 0.0f },
        (vec2) { 1.0f, 1.0f },
        (vec2) { 0.0f, 0.0f },
        (vec4) { 0.7725f, 0.1490f, 0.4705f, 1.0f }
    );

    Entity* top_wall = entity_create (
        (vec2) { -16.0f, 8.0f },
        (vec2) { 40.0f, 1.0f },
        (vec2) { 0.0f, 0.0f },
        (vec4) { 0.7725f, 0.1490f, 0.4705f, 1.0f }
    );

    Entity* bot_wall = entity_create (
        (vec2) { -16.0f, -9.0f },
        (vec2) { 40.0f, 1.0f },
        (vec2) { 0.0f, 0.0f },
        (vec4) { 0.7725f, 0.1490f, 0.4705f, 1.0f }
    );

    Entity* right_wall = entity_create (
        (vec2) { 15.0f, -9.0f },
        (vec2) { 1.0f, 20.0f },
        (vec2) { 0.0f, 0.0f },
        (vec4) { 0.7725f, 0.1490f, 0.4705f, 1.0f }
    );
    
    Entity* left_wall = entity_create (
        (vec2) { -16.0f, -9.0f },
        (vec2) { 1.0f, 20.0f },
        (vec2) { 0.0f, 0.0f },
        (vec4) { 0.7725f, 0.1490f, 0.4705f, 1.0f }
    );

    entity_set_collider(player_1, collider_create(player_1->position, player_1->scale));
    entity_set_collider(player_2, collider_create(player_2->position, player_2->scale));
    entity_set_collider(ball, collider_create(ball->position, ball->scale));
    entity_set_collider(top_wall, collider_create(top_wall->position, top_wall->scale));
    entity_set_collider(bot_wall, collider_create(bot_wall->position, bot_wall->scale));
    entity_set_collider(left_wall, collider_create(left_wall->position, left_wall->scale));
    entity_set_collider(right_wall, collider_create(right_wall->position, right_wall->scale));
    
    /* Graphics setup */
    GLuint rect_shader = shader_create_from_file("assets/vsh_rect.glsl", "assets/fsh_rect.glsl");
    GLuint circle_shader = shader_create_from_file("assets/vsh_circle.glsl", "assets/fsh_circle.glsl");

    entity_set_rect(player_1, rect_create(rect_shader));
    entity_set_rect(player_2, rect_create(rect_shader));
    entity_set_rect(ball, rect_create(circle_shader));
    entity_set_rect(top_wall, rect_create(rect_shader));
    entity_set_rect(bot_wall, rect_create(rect_shader));
    entity_set_rect(left_wall, rect_create(rect_shader));
    entity_set_rect(right_wall, rect_create(rect_shader));

    /* Space Setup */ 
    mat4 mvp_matrix;
    renderer_config_mvp_matrix(&mvp_matrix);

    /* Time Setup */
    double current_frame_time = glfwGetTime();
    double delta_time         = 0.0;
    double last_frame_time    = 0.0;

    /* Game loop */
    log_info("Running game...");

    while (!glfwWindowShouldClose(window)) {
        renderer_clear_screen();
        
        /* Input */
        input_check_quit(window);
        vec2 p1_direction = { 0.0, input_get_vertical(window, P1) };
        vec2 p2_direction = { 0.0, input_get_vertical(window, P2) };

        /* Time update */
        current_frame_time  = glfwGetTime();
        delta_time          = current_frame_time - last_frame_time;
        last_frame_time     = current_frame_time;

        /* Players */
        glm_vec2_scale(p1_direction, player_1_speed * delta_time, player_1->velocity);
        entity_translate(player_1, player_1->velocity);

        glm_vec2_scale(p2_direction, player_2_speed * delta_time, player_2->velocity);
        entity_translate(player_2, player_2->velocity);
    
        /* Ball */
        glm_vec2_scale(ball_direction, ball_speed * delta_time, ball->velocity);
        entity_translate(ball, ball->velocity);

        entity_check_collision(ball, player_1, ENTER, ball_paddle_bounce);
        entity_check_collision(ball, player_2, ENTER, ball_paddle_bounce);
        entity_check_collision(ball, top_wall, ENTER, ball_top_wall_bounce);
        entity_check_collision(ball, bot_wall, ENTER, ball_bot_wall_bounce);
        entity_check_collision(ball, left_wall, ENTER, ball_left_wall_bounce);
        entity_check_collision(ball, right_wall, ENTER, ball_right_wall_bounce);

        /* Render */
        renderer_draw_entity(player_1, mvp_matrix);
        renderer_draw_entity(player_2, mvp_matrix);
        renderer_draw_entity(ball, mvp_matrix);
        renderer_draw_entity(top_wall, mvp_matrix);
        renderer_draw_entity(bot_wall, mvp_matrix);
        renderer_draw_entity(left_wall, mvp_matrix);
        renderer_draw_entity(right_wall, mvp_matrix);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    entity_dispose(player_1);
    entity_dispose(player_2);
    entity_dispose(ball);
    entity_dispose(top_wall);
    entity_dispose(bot_wall);
    entity_dispose(left_wall);
    entity_dispose(right_wall);

    glfwDestroyWindow(window);
    glfwTerminate();

    printf("%s", "\n");
    log_info("Game closed, Bye bye.");
    return 0;
}
