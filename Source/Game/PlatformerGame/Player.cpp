#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include"Renderer/ModelManager.h"
#include "Audio/AudioSystem.h"
#include "Core/Math/MathUtils.h"


#include "Framework/Framework.h"

namespace kiko {
	CLASS_DEFINITION(Player)

		bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		m_spriteComponent = GetComponent<SpriteAnimRenderComponent>();
	
		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		float dir = 0;
		if (g_InputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (g_InputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;
		//transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

		vec2 forward = vec2{ 1,0 };

		m_physicsComponent->ApplyForce(forward * speed * dir);


		bool onGround = (groundCount > 0);
		

		if (onGround && kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_InputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
			kiko::vec2 up = kiko::vec2{ 0,-1 };
			m_physicsComponent->SetVelocity(up * jump);
		}

		//animation
		vec2 velocity = m_physicsComponent->m_velocity;
		if (std::fabs(velocity.x) > 0.2f)
		{
			if(dir!=0)m_spriteComponent->flipH = (dir < 0);
			m_spriteComponent->SetSequence("idle");
		}
		else
		{
			m_spriteComponent->SetSequence("idle");
		}

	}
	void Player::OnCollissionEnter(Actor* other)
	{
		if (other->tag == "Ground") groundCount++;
		
	}

	void Player::OnCollissionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;

	}

	void Player::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}