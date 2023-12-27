#ifndef NODE_H
#define NODE_H

#include <CGLM/include/cglm/vec2.h>
#include <CGLM/include/cglm/vec4.h>
#include "collider.h"

typedef struct node {
    vec2 position;
    vec2 scale;
    Collider* collider;
    vec2 velocity;
    vec4 color;
} Node;

Node* node_create          (vec2 position, vec2 scale, Collider* collider, vec2 velocity, vec4 color);
void node_set_position     (Node* node, vec2 position);
void node_set_scale        (Node* node, vec2 scale);
void node_set_collider     (Node* node, Collider* node_get_collider);
void node_set_velocity     (Node* node, vec2 velocity);
void node_set_color        (Node* node, vec4 color);

float* node_get_position   (Node* node);
float* node_get_scale      (Node* node);
Collider node_get_collider (Node* node);
float* node_get_velocity   (Node* node);
//float* node_get_color     (Node* node);

#endif /* NODE_H */