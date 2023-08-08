#pragma once
#include "Framework/Actor.h"

class Player : public kiko::Actor
{
public:
	Player(float speed, float turnRate, const kiko::Transform& transform) :
		Actor{ transform},
		m_speed { speed },
		m_turnRate{ turnRate }
	{}

	void Update(float dt) override;
	void OnCollission(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
	int m_health = 100;
};