#pragma once
#include <string>
#include <memory>

#include "glm/glm.hpp"
#include "EntityTypes.h"
#include <iostream>

class Entity
{
public:
    Entity(const glm::vec2& pos, const glm::vec2& direction, float speed)
        : m_Position(pos)
        , m_Direction(glm::normalize(direction))
        , m_Speed(speed)
    {}

    Entity(const EntityParams& params)
        : m_Position(params.position)
        , m_Direction(glm::normalize(params.direction))
        , m_Speed(params.speed)
    {}

    virtual void Update(float deltaTime);
    virtual std::string ToString() const;

    const glm::vec2& getPosition() const { return m_Position; }
    const glm::vec2& getDirection() const { return m_Direction; }
    const glm::vec2& getVelocity() const { return m_Direction * m_Speed; }

protected:
    glm::vec2 m_Position;
    glm::vec2 m_Direction;
    float m_Speed;
};

class Rocket : public Entity
{
public:
    Rocket(const glm::vec2& pos, const glm::vec2& direction, float velocity, float radius)
        : Entity(pos, direction, velocity)
        , m_Radius(radius)
    {}

    Rocket(const EntityParams& params, float radius)
        : Entity(params)
        , m_Radius(radius)
    {}

    Rocket(const RocketParams& params)
        : Entity(params)
        , m_Radius(abs(params.radius))
    {}

    virtual void Update(float deltaTime) override;
    virtual std::string ToString() const override;

    void SetTarget(std::shared_ptr<Entity> target);
    void UpdateDirection(float deltaTime);
    bool IsTargetOverlap();

protected:
    float m_Radius;
    std::weak_ptr<Entity> m_Target;
};

