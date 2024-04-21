#ifndef ENTITY_H
#define ENTITY_H

#include <CGLM/include/cglm/vec2.h>
#include <CGLM/include/cglm/vec4.h>
#include "../render/primitives/rect.h"
#include "collider.h"

typedef struct entity {
    vec2 position;
    vec2 scale;
    vec2 velocity;
    vec4 color;
    Collider* collider;
    Rect* rect;
} Entity;

Entity* entity_create        (vec2 position, vec2 scale, vec2 velocity, vec4 color);
void entity_set_position     (Entity* entity, vec2 position);
void entity_set_scale        (Entity* entity, vec2 scale);
void entity_set_velocity     (Entity* entity, vec2 velocity);
void entity_set_color        (Entity* entity, vec4 color);
void entity_set_collider     (Entity* entity, Collider* collider);
void entity_set_rect         (Entity* entity, Rect* rect);

float* entity_get_position   (Entity* entity);
float* entity_get_scale      (Entity* entity);
float* entity_get_velocity   (Entity* entity);
Collider entity_get_collider (Entity* entity);
Rect* entity_get_rect        (Entity* entity);

void entity_dispose(Entity* entity);

#endif /* ENTITY_H */