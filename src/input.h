#ifndef INPUT_H
#define INPUT_H

#include <CGLM/include/cglm/vec2.h>
#include <GLFW/glfw3.h>

#define KEY_QUIT_APP        GLFW_KEY_ESCAPE
#define KEY_START_GAME      GLFW_KEY_SPACE

#define KEY_PLAYER_1_UP     GLFW_KEY_W
#define KEY_PLAYER_1_DOWN   GLFW_KEY_S
#define KEY_PLAYER_1_RIGHT  GLFW_KEY_A      /* Not very useful but... why not? */
#define KEY_PLAYER_1_LEFT   GLFW_KEY_D      /* ...                             */

#define KEY_PLAYER_2_UP     GLFW_KEY_UP
#define KEY_PLAYER_2_DOWN   GLFW_KEY_DOWN
#define KEY_PLAYER_2_RIGHT  GLFW_KEY_RIGHT  /* ...                              */
#define KEY_PLAYER_2_LEFT   GLFW_KEY_LEFT   /* ...                              */

enum PLAYER { PLAYER_1, PLAYER_2 };
extern enum PLAYER P1; /* extern indicates that the variable will be initialized elsewhere (in this case input.c) */
extern enum PLAYER P2;

void  input_check_quit(GLFWwindow* window);
float input_get_vertical(GLFWwindow* window, enum PLAYER player);

#endif /* INPUT_H */