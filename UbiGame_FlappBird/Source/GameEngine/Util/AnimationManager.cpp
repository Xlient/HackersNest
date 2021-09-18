#include "AnimationManager.h"


using namespace GameEngine;

AnimationManager* AnimationManager::sm_instance = nullptr;

AnimationManager::AnimationManager()
{

}


AnimationManager::~AnimationManager()
{

}


void AnimationManager::InitStaticGameAnimations()
{
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerIdle,
			eTexture::Player,
			sf::Vector2i(0, 0),
			7,
			4)
	);

	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerJump,
			eTexture::Player,
			sf::Vector2i(1, 10),
			15,
			12)
	);

	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerMove,
			eTexture::Player,
			sf::Vector2i(5,  2),
			4,
			4)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerAttackLeft,
			eTexture::Player,
			sf::Vector2i(4, 3),
			10,
			15)
	);

	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerAttackRight,
			eTexture::Player,
			sf::Vector2i(5, 4),
			10,
			15)
	);
}


void AnimationManager::ReleaseStaticGameAnimations()
{
	m_animDefinitions.clear();
}


const SAnimationDefinition* AnimationManager::GetAnimDefinition(EAnimationId::type animId) const
{
	for (int a = 0; a < m_animDefinitions.size(); ++a)
	{
		if (m_animDefinitions[a].m_animId == animId)
			return &m_animDefinitions[a];
	}

	return nullptr;
}
