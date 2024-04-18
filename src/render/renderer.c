#include "renderer.h"

void renderer_set_clearcolor(float r, float g, float b, float a) {
    GL_CALL(glClearColor(r, g, b, a));
}

void renderer_clear_screen() {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}
