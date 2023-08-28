#include "PlatformGame.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/ModelManager.h"


bool PlatformGame::Initialize()
{
	//load audio
	kiko::g_AudioSystem.AddAudio("laser", "laser-gun.wav");
	kiko::g_AudioSystem.AddAudio("music", "music.wav");

	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("Scenes/PlatformerScene.json");
	m_scene->Initialize();



	/*std::vector<Enemey> enemies;
	for (int i = 0; i < 5; i++) {
		std::unique_ptr<Enemey> enemey = std::make_unique<Enemey>(10.0f, kiko::Pi, kiko::Transform{ {kiko::random(600), kiko::random(600)}, kiko::randomf(kiko::TwoPi), 3 }, kiko::g_manager.Get("ship.txt"));
		enemey->m_tag = "Enemey";
		m_scene->Add(move(enemey));
	}*/

	EVENT_SUBSCRIBE("AddPoints", PlatformGame::AddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead);

	//kiko::EventManager::Instance().Subscribe("AddPoints", this, std::bind(&PlatformGame::AddPoints, this, std::placeholders::_1));
	//kiko::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&PlatformGame::OnPlayerDead, this, std::placeholders::_1));

	return true;
}

void PlatformGame::Shutdown()
{
}

void PlatformGame::Update(float dt)
{
	switch (m_state)
	{
	case PlatformGame::eState::Title:
		m_scene->GetActorByName("Title")->active = true;

		if (kiko::g_InputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			auto actor = m_scene->GetActorByName("Background");
			if (actor == nullptr)
			{
				WARNING_LOG("Actor doesn't exist")
					break;
			}

			m_scene->GetActorByName("Title")->active = false;
		}
		break;
	case PlatformGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case PlatformGame::eState::StartLevel:
		m_scene->RemoveAll();
		
		m_state = eState::Game;
		break;
	case PlatformGame::eState::Game:
	
		break;
	case PlatformGame::eState::PlayerDeadStart:
		
		if (m_lives == 0) { m_state = eState::GameOver; }
		else m_state = eState::PlayerDead;

		break;
	case PlatformGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}


		break;
	case PlatformGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer == 0)
		{
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}
	m_scene->Update(dt);
}

void PlatformGame::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);

	kiko::g_particleSystem.Draw(renderer);
}

void PlatformGame::AddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const kiko::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}
