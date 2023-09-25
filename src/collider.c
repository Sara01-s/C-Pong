#include "collider.h"
#include "utils.h"

bool collider_check(vec2 collider[2], vec2 other[2]) {
    return (collider[1][X] <= other[2][X] && collider[2][X] >= other[1][X])
        && (collider[1][Y] <= other[2][Y] && collider[2][Y] >= other[1][Y]);
}

void collider_follow_position(vec2 collider[2], vec2 target_position) {
    glm_vec2_add(collider[1], target_position, collider[1]);
    glm_vec2_add(collider[2], target_position, collider[2]);
}