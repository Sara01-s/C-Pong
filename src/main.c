#include <CGLM/include/cglm/struct.h>
#include <CGLM/include/cglm/io.h>

#include "utils.h"

#include "render/renderer.h"
#include "render/primitives/rect.h"

#include "game/input.h"
#include "game/entity.h"
#include "game/collider.h"

const unsigned long long MAX_GAME_VERTICES = 1024ULL; /* 1kb */

float player_1_speed = 100.0f;
float player_2_speed = 100.0f;

vec2  ball_direction = { 1.0f, 0.0f };
float ball_speed     = 10.0f;

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

    entity_set_collider(player_1, collider_create(player_1->position, player_1->scale));
    entity_set_collider(player_2, collider_create(player_2->position, player_2->scale));
    entity_set_collider(ball, collider_create(ball->position, ball->scale));
    
    /* Graphics setup */
    GLuint rect_shader = shader_create_from_file("assets/vsh_rect.glsl", "assets/fsh_rect.glsl");
    GLuint circle_shader = shader_create_from_file("assets/vsh_circle.glsl", "assets/fsh_circle.glsl");

    entity_set_rect(player_1, rect_create(rect_shader));
    entity_set_rect(player_2, rect_create(rect_shader));
    entity_set_rect(ball, rect_create(circle_shader));

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
    

        /* Ball */
        glm_vec2_scale(ball_direction, ball_speed * delta_time, ball->velocity);
        entity_translate(ball, ball->velocity);

        collider_follow_position(ball->collider, ball->position);

        if (collider_check_stay(*ball->collider, *player_2->collider)) {
            log_info("COLISIOOOOOON");
        }


        /* Render */
        renderer_draw_entity(player_1, mvp_matrix);
        renderer_draw_entity(player_2, mvp_matrix);
        renderer_draw_entity(ball, mvp_matrix);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    entity_dispose(player_1);
    entity_dispose(player_2);
    entity_dispose(ball);

    printf("%s", "\n");
    log_info("Game closed, Bye bye.");
    return 0;
}
