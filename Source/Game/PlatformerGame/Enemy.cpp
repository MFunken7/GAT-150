#include "Enemy.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include"Renderer/ModelManager.h"
#include "Audio/AudioSystem.h"
#include "Core/Math/MathUtils.h"


#include "Framework/Framework.h"

namespace kiko {
	CLASS_DEFINITION(Enemy)

		bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();

		return true;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		float dir = 0;
		if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;
		//transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

		kiko::vec2 forward = kiko::vec2{ 1,0 };

		m_physicsComponent->ApplyForce(forward * speed * dir);


		bool onGround = (groundCount > 0);


		if (onGround && kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_InputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			kiko::vec2 up = kiko::vec2{ 0,-1 };
			m_physicsComponent->SetVelocity(up * jump);
		}


	}
	void Enemy::OnCollissionEnter(Actor* other)
	{
		if (other->tag == "Ground") groundCount++;

	}

	void Enemy::OnCollissionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;

	}

	void Enemy::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}