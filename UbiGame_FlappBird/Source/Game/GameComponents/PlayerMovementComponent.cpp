#include "PlayerMovementComponent.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"

#include "GameEngine/Util/TextureManager.h"
#include "GameEngine/Util/AnimationManager.h"

#include "Game/GameComponents/PlayerSoundComponent.h"

#include <SFML/Window/Keyboard.hpp>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
	: m_flyTimerDt(0.f)
	, m_flyTimerMaxTime(2.f)
	, m_animComponent(nullptr)
	, m_playerSoundComponent(nullptr)
{

}


PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::OnAddToWorld()
{
	m_animComponent = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
	m_playerSoundComponent = GetEntity()->GetComponent<PlayerSoundComponent>();
}


void PlayerMovementComponent::Update()
{
	Component::Update();

	if (GameEngine::GameEngineMain::GetInstance()->IsGameOver())
	{
		return;
	}

	float dt = GameEngine::GameEngineMain::GetTimeDelta();
	static float playerVel = 150.f; //Pixels/s

	sf::Vector2f wantedVel = sf::Vector2f(0.f, 0.f);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			wantedVel.x -= playerVel * dt;
			m_arrowKeyPressed = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			wantedVel.x += playerVel * dt;
			m_arrowKeyPressed = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			wantedVel.y -= playerVel * dt;
			m_arrowKeyPressed = true;
			if (m_playerSoundComponent)
			{
				m_playerSoundComponent->RequestSound(true);
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			wantedVel.y += playerVel * dt;
			m_arrowKeyPressed = true;
			if (m_playerSoundComponent)
			{
				m_playerSoundComponent->RequestSound(false);
			}
		}
		else 
		{
			if (m_animComponent) 
			{
				m_animComponent->PlayAnim(GameEngine::EAnimationId::PlayerMove, true);
			}

			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			if (m_animComponent)
			{
				m_animComponent->PlayAnim(GameEngine::EAnimationId::PlayerJump, true);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (m_animComponent)
			{
				m_animComponent->PlayAnim(GameEngine::EAnimationId::PlayerAttackLeft, true);
				
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			if (m_animComponent)
			{
				m_animComponent->PlayAnim(GameEngine::EAnimationId::PlayerAttackRight, false);
			}
		}
	
	
	
	GetEntity()->SetPos(GetEntity()->GetPos() + wantedVel);


	// To do 
	if (wantedVel != sf::Vector2f(0.f, 0.f))
	{
		m_flyTimerDt = m_flyTimerMaxTime;
	}
	else
	{
		m_flyTimerDt -= dt;
	}
	
	

	
	static float rotationVel = 50.f; //Deg/s
	static float maxRotation = 20.f; //Deg
	
	float currentRotation = GetEntity()->GetRot();
	float wantedRot = 0.f;
	bool  reseting = false;

	if (wantedVel.y > 0.f)
		wantedRot = rotationVel;
	else if (wantedVel.y < 0.f)
		wantedRot = -rotationVel;
	else
	{				
		if (currentRotation > 0.f)
			wantedRot = -rotationVel;
		else if (currentRotation < 0.f)
			wantedRot = rotationVel;
	}

	float frameRot = wantedRot * dt;
	float totalRot = currentRotation + frameRot;

	if (!reseting)
	{
		if (totalRot > maxRotation)
			totalRot = maxRotation;
		else if (totalRot < -maxRotation)
			totalRot = -maxRotation;
	}
	else
	{
		if (currentRotation > 0.f && totalRot < 0.f)
			totalRot = 0.f;
		if (currentRotation < 0.f && totalRot > 0.f)
			totalRot = 0.f;
	}

	GetEntity()->SetRotation(totalRot);
}