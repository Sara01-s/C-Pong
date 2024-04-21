#include "collider.h"
#include "../utils.h"

Collider* collider_create(vec2 position, vec2 scale) {
    Collider* collider = malloc(sizeof(Collider));

    glm_vec2_copy(position, collider->position);
    glm_vec2_copy(scale, collider->scale);
    glm_vec2_sub(collider->position, collider->scale, collider->lh_vector);
    glm_vec2_add(collider->position, collider->scale, collider->rh_vector);

    return collider;
}

bool collider_check_stay(Collider collider, Collider other) {
    float c_pos_x  = collider.position[X];
    float c_pos_y  = collider.position[Y];
    float c_width  = collider.scale[X];
    float c_height = collider.scale[Y];

    float o_pos_x  = other.position[X];
    float o_pos_y  = other.position[Y];
    float o_width  = other.scale[X];
    float o_height = other.scale[Y];

    bool collision = (c_pos_x < o_pos_x  + o_width)
                  && (c_pos_x + c_width  > o_pos_x)
                  && (c_pos_y < o_pos_y  + o_height)
                  && (c_pos_y + c_height > o_pos_y);

    return collision;
}

void collider_follow_position(Collider* collider, vec2 target_position) {

    float col_width  = collider->scale[X];
    float col_height = collider->scale[Y];

    float target_x = target_position[X];
    float target_y = target_position[Y];

    float col_target_x1 = target_x - col_width;
    float col_target_y1 = target_y - col_height;

    float col_target_x2 = target_x + col_width;
    float col_target_y2 = target_y + col_height;

    collider->lh_vector[X] = col_target_x1;
    collider->lh_vector[Y] = col_target_y1;
    collider->rh_vector[X] = col_target_x2;
    collider->rh_vector[Y] = col_target_y2;
}
