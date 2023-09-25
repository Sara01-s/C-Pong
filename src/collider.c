#include "collider.h"
#include "utils.h"

bool collider_check(vec2 collider[2], vec2 other[2]) {
    return (other[1] >= collider[1] && collider[1] >= other[0]);
}

void collider_follow_position(vec2 collider[2], vec2 target_position) {
    glm_vec2_add(collider[0], target_position, collider[0]);
    glm_vec2_add(collider[1], target_position, collider[1]);
}