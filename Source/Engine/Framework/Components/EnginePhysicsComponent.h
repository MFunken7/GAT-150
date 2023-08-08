#pragma once
#include "PhysicsComponent.h"

namespace kiko
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:
		virtual void Update(float dt) override;
		virtual void ApplyForce(vec2 force) override;

	};
}