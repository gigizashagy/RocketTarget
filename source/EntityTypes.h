#pragma once
#include "glm/glm.hpp"

struct EntityParams
{
    glm::vec2 position = { 0.f ,0.f };
    glm::vec2 direction = { 0.f ,0.f };
    float speed = 0.f;
};

struct RocketParams : EntityParams
{
    float radius = 0.f;
};