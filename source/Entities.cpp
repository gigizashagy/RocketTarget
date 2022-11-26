#include "Entities.h"

#include "glm/gtx/string_cast.hpp"
#include "utilities.h"

void Entity::Update(float deltaTime)
{
	m_Position += m_Direction * m_Speed * deltaTime;
}

std::string Entity::ToString() const
{
	return string_format("Entity:\tDirection: %s Position: %s", glm::to_string(m_Direction).c_str(), glm::to_string(m_Position).c_str());
}

void Rocket::SetTarget(std::shared_ptr<Entity> target)
{
	m_Target = target;
}

void Rocket::UpdateDirection(float deltaTime)
{
	const float maxDist = 10.f;
	const float clampDistance = Clamp(glm::distance(m_Position, m_Target.lock()->getPosition()), 0.f, maxDist);
	const float tDist = clampDistance / maxDist;

	const float maxCoeff = 5.f;
	const float minCoeff = 0.f;

	float coeff = Clamp(tDist, minCoeff, maxCoeff);
	auto targetPoint = m_Target.lock()->getPosition() + (m_Target.lock()->getDirection() * (m_Radius * coeff)) * deltaTime;
	m_Direction = glm::normalize(targetPoint - m_Position);
}

void Rocket::Update(float deltaTime)
{
	if (!m_Target.expired())
	{
		UpdateDirection(deltaTime);
	}
	Entity::Update(deltaTime);
}

bool Rocket::IsTargetOverlap()
{
	if (!m_Target.expired())
	{
		return glm::length(m_Target.lock()->getPosition() - m_Position) < m_Radius;
	}
	return false;
}

std::string Rocket::ToString() const
{
	return string_format("Rocket:\tDirection: %s Position: %s", glm::to_string(m_Direction).c_str(), glm::to_string(m_Position).c_str());
}
