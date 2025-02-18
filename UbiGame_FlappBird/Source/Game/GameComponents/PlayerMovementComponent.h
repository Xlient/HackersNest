#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"
#include "GameEngine/Util/SoundManager.h"

namespace Game
{	
	class PlayerSoundComponent;

	class PlayerMovementComponent : public GameEngine::Component
	{
	public:
		PlayerMovementComponent();
		~PlayerMovementComponent();

		virtual void Update() override;
		virtual void OnAddToWorld() override;

	private:
		float m_flyTimerDt;
		float m_flyTimerMaxTime;
		bool m_arrowKeyPressed;
		bool m_attackButtonPressed;
		bool m_jumpButtonPressed;
		bool m_bulidButtonPressed;


		GameEngine::AnimationComponent* m_animComponent;
		PlayerSoundComponent*			m_playerSoundComponent;
	};
}


