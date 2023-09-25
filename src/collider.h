#ifndef COLLIDER_H
#define COLLIDER_H

#include <stdbool.h>
#include <CGLM/include/cglm/vec2.h>

/* aabb collision 2D */
bool collider_check(vec2 collider[2], vec2 other[2]);
void collider_follow_position(vec2 collider[2], vec2 target_position);

#endif /* COLLIDER_H */