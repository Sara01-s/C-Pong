#include <string.h>
#include "entity.h"

Entity* entity_create(vec2 position, vec2 scale, Collider* collider, vec2 velocity, vec4 color) {

    Entity* entity = malloc(sizeof(Entity));
    glm_vec2_copy(position, entity->position);
    glm_vec2_copy(scale, entity->scale);
    entity->collider = collider;
    glm_vec2_copy(velocity, entity->velocity);
    glm_vec4_copy(color, entity->color);

    return entity;
}

void entity_set_position(Entity* entity, vec2 position) {
    glm_vec2_copy(position, entity->position);
}

void entity_set_scale(Entity* entity, vec2 scale) {
    glm_vec2_copy(scale, entity->scale);
}

void entity_set_collider(Entity* entity, Collider* collider) {
    entity->collider = collider;
}

void entity_set_velocity(Entity* entity, vec2 velocity) {
    glm_vec2_copy(velocity, entity->velocity);
}

void entity_set_color(Entity* entity, vec4 color) {
    glm_vec4_copy(color, entity->color);
}

float* entity_get_position(Entity* entity) {
    return entity->position;
}

float* entity_get_scale(Entity* entity) {
    return entity->scale;
}

Collider entity_get_collider(Entity* entity) {
    return *entity->collider;
}

float* entity_get_velocity(Entity* entity) {
    return entity->velocity;
}

void entity_dispose(Entity* entity) {
    free(entity->collider);
    free(entity);
}
