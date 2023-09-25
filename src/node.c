#include <string.h>
#include "node.h"

Node* node_create(vec2 position, vec2 scale, vec2 collider[2], vec2 velocity, vec4 color) {

    Node* node = malloc(sizeof(Node));
    glm_vec2_copy(position, node->position);
    glm_vec2_copy(scale, node->scale);
    memcpy(&node->collider[0][0], &collider[0][0], 4 * sizeof(float));
    glm_vec2_copy(velocity, node->velocity);
    glm_vec4_copy(color, node->color);

    return node;
}

void node_set_position(Node* node, vec2 position) {
    glm_vec2_copy(position, node->position);
}

void node_set_scale(Node* node, vec2 scale) {
    glm_vec2_copy(scale, node->scale);
}

void node_set_collider(Node* node, vec2 collider[2]) {
    memcpy(&node->collider[0][0], &collider[0][0], 4 * sizeof(float));
}

void node_set_velocity(Node* node, vec2 velocity) {
    glm_vec2_copy(velocity, node->velocity);
}

void node_set_color(Node* node, vec4 color) {
    glm_vec4_copy(color, node->color);
}

float* node_get_position(Node* node) {
    return node->position;
}

float* node_get_scale(Node* node) {
    return node->scale;
}

float* node_get_collider(Node* node) {
    return node->collider[0];
}

float* node_get_velocity(Node* node) {
    return node->velocity;
}
