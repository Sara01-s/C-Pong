#ifndef ENTITY_H
#define ENTITY_H

#include <CGLM/include/cglm/vec2.h>
#include <CGLM/include/cglm/vec4.h>
#include "collider.h"

typedef struct entity {
    vec2 position;
    vec2 scale;
    Collider* collider;
    vec2 velocity;
    vec4 color;
} Entity;

Entity* entity_create        (vec2 position, vec2 scale, Collider* collider, vec2 velocity, vec4 color);
void entity_set_position     (Entity* entity, vec2 position);
void entity_set_scale        (Entity* entity, vec2 scale);
void entity_set_collider     (Entity* entity, Collider* collider);
void entity_set_velocity     (Entity* entity, vec2 velocity);
void entity_set_color        (Entity* entity, vec4 color);

float* entity_get_position   (Entity* entity);
float* entity_get_scale      (Entity* entity);
Collider entity_get_collider (Entity* entity);
float* entity_get_velocity   (Entity* entity);
//float* entity_get_color     (entity* entity);

void entity_dispose(Entity* entity);

#endif /* ENTITY_H */