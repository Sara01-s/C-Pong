#include <stdio.h>
#include "input.h"

enum PLAYER P1 = PLAYER_1;
enum PLAYER P2 = PLAYER_2;

typedef struct {
    float vertical;
    float horizontal;
} InputAxes;

InputAxes playerAxes[2] = { {0.0f, 0.0f}, {0.0f, 0.0f} };
const float inputIncrement = 0.1f;

void input_check_quit(GLFWwindow* window) {
    if (glfwGetKey(window, KEY_QUIT_APP) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void input_get_axis(GLFWwindow* window, InputAxes* axes, int keyUp, int keyDown, int keyLeft, int keyRight) {
    axes->vertical = 0.0f;
    axes->horizontal = 0.0f;

    if (glfwGetKey(window, keyUp)) axes->vertical += inputIncrement;
    if (glfwGetKey(window, keyDown)) axes->vertical -= inputIncrement;
    if (glfwGetKey(window, keyRight)) axes->horizontal += inputIncrement;
    if (glfwGetKey(window, keyLeft)) axes->horizontal -= inputIncrement;

    axes->vertical = glm_clamp(axes->vertical, -1.0f, 1.0f);
    axes->horizontal = glm_clamp(axes->horizontal, -1.0f, 1.0f);
}

float input_get_vertical(GLFWwindow* window, enum PLAYER player) {
    input_get_axis(window, &playerAxes[player], 
                   player == PLAYER_1 ? KEY_PLAYER_1_UP : KEY_PLAYER_2_UP,
                   player == PLAYER_1 ? KEY_PLAYER_1_DOWN : KEY_PLAYER_2_DOWN,
                   player == PLAYER_1 ? KEY_PLAYER_1_LEFT : KEY_PLAYER_2_LEFT,
                   player == PLAYER_1 ? KEY_PLAYER_1_RIGHT : KEY_PLAYER_2_RIGHT);

    return playerAxes[player].vertical;
}

float input_get_horizontal(GLFWwindow* window, enum PLAYER player) {
    input_get_axis(window, &playerAxes[player], 
                   player == PLAYER_1 ? KEY_PLAYER_1_UP : KEY_PLAYER_2_UP,
                   player == PLAYER_1 ? KEY_PLAYER_1_DOWN : KEY_PLAYER_2_DOWN,
                   player == PLAYER_1 ? KEY_PLAYER_1_LEFT : KEY_PLAYER_2_LEFT,
                   player == PLAYER_1 ? KEY_PLAYER_1_RIGHT : KEY_PLAYER_2_RIGHT);

    return playerAxes[player].horizontal;
}