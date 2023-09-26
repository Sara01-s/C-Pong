#include "collider.h"
#include "utils.h"

float* collider_lh_x(vec2 collider[2]) {
    return &(collider[0][X]);
}

float* collider_lh_y(vec2 collider[2]) {
    return &(collider[0][Y]);
}

float* collider_rh_x(vec2 collider[2]) {
    return &(collider[1][X]);
}

float* collider_rh_y(vec2 collider[2]) {
    return &(collider[1][Y]);
}

float collider_width(vec2 collider[2]) {
    float x1 = *collider_lh_x(collider);
    float x2 = *collider_rh_x(collider);
    return x2 - x1;
}

float collider_height(vec2 collider[2]) {
    float y1 = *collider_lh_y(collider);
    float y2 = *collider_rh_y(collider);
    return y2 - y1;
}

bool collider_check_stay(vec2 collider[2], vec2 other[2]) {
    float c_pos_x  = *collider_lh_x(collider) + *collider_rh_x(collider) / 2.0f;
    float c_pos_y  = *collider_lh_y(collider) + *collider_rh_y(collider) / 2.0f;
    float c_width  = collider_width(collider);
    float c_height = collider_height(collider);

    float o_pos_x  = *collider_lh_x(other) + *collider_rh_x(other) / 2.0f;
    float o_pos_y  = *collider_lh_y(other) + *collider_rh_y(other) / 2.0f;
    float o_width  = collider_width(other);
    float o_height = collider_height(other);

    bool collision = (c_pos_x < o_pos_x  + o_width)
                  && (c_pos_x + c_width  > o_pos_x)
                  && (c_pos_y < o_pos_y  + o_height)
                  && (c_pos_y + c_height > o_pos_y);

    return collision;
}

void collider_follow_position(vec2 collider[2], vec2 target_position) {

    float x1 = *collider_lh_x(collider);
    float x2 = *collider_rh_x(collider);
    float col_width = (x2 - x1) / 2.0f;

    float y1 = *collider_lh_y(collider);
    float y2 = *collider_rh_y(collider);
    float col_height = (y2 - y1) / 2.0f;

    float target_x = target_position[X];
    float target_y = target_position[Y];

    float col_target_x1 = target_x - col_width;
    float col_target_y1 = target_y - col_height;

    float col_target_x2 = target_x + col_width;
    float col_target_y2 = target_y + col_height;

    *collider_lh_x(collider) = col_target_x1;
    *collider_lh_y(collider) = col_target_y1;
    *collider_rh_x(collider) = col_target_x2;
    *collider_rh_y(collider) = col_target_y2;
}