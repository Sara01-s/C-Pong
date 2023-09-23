#include <stdio.h>
#include "input.h"

enum PLAYER P1 = PLAYER_1;
enum PLAYER P2 = PLAYER_2;

typedef struct {
    float vertical_axis;
    float horizontal_axis;
} InputAxes;

InputAxes player_1_axes = { 0.0f, 0.0f };
InputAxes player_2_axes = { 0.0f, 0.0f };
float input_increment = 0.1f;

void input_check_quit(GLFWwindow* window) {
    if (glfwGetKey(window, KEY_QUIT_APP)) {
        glfwSetWindowShouldClose(window, true);
    }
}

void input_get_axis(GLFWwindow* window, InputAxes* axis, int key_up, int key_down, int key_left, int key_right) {
    if (glfwGetKey(window, key_up))
        axis->vertical_axis += input_increment;
    else if (glfwGetKey(window, key_down))
        axis->vertical_axis -= input_increment;
    else
        axis->vertical_axis = 0.0f;

    if (glfwGetKey(window, key_right))
        axis->horizontal_axis += input_increment;
    else if (glfwGetKey(window, key_left))
        axis->horizontal_axis -= input_increment;
    else
        axis->horizontal_axis = 0.0f;

    axis->vertical_axis   = glm_clamp(axis->vertical_axis, -1.0f, 1.0f);
    axis->horizontal_axis = glm_clamp(axis->horizontal_axis, -1.0f, 1.0f);
}

float input_get_vertical(GLFWwindow* window, enum PLAYER player) {
    if (player == PLAYER_1) {
        input_get_axis(window, &player_1_axes, KEY_PLAYER_1_UP, KEY_PLAYER_1_DOWN, KEY_PLAYER_1_LEFT, KEY_PLAYER_1_RIGHT);
        return player_1_axes.vertical_axis;
    }
    else if (player == PLAYER_2) {
        input_get_axis(window, &player_2_axes, KEY_PLAYER_2_UP, KEY_PLAYER_2_DOWN, KEY_PLAYER_1_LEFT, KEY_PLAYER_1_RIGHT);
        return player_2_axes.vertical_axis;
    }

    return 0.0f;
}
