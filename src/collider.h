#ifndef COLLIDER_H
#define COLLIDER_H

#include <stdbool.h>
#include <CGLM/include/cglm/vec2.h>

typedef struct collider {
    vec2 position;
    vec2 scale;
    vec2 lh_vector;
    vec2 rh_vector;
} Collider;

/* aabb collision 2D */
/* Don't forget to free() colliders :) */
Collider* collider_create(vec2 position, vec2 scale);
bool collider_check_stay(Collider collider, Collider other);
void collider_follow_position(Collider* collider, vec2 target_position);

#endif /* COLLIDER_H */