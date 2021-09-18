#include "GameBoard.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/TextRenderComponent.h"
#include "GameEngine/Util/CameraManager.h"
#include "Game/GameEntities/PlayerEntity.h"
#include "Game/GameEntities/ObstacleEntity.h"


using namespace Game;

GameBoard::GameBoard()
	: m_player(nullptr)
{
	CreatePlayer();
	CreateBackground();
}


GameBoard::~GameBoard()
{

}


void GameBoard::Update()
{	
	
}

void GameBoard::CreatePlayer() 
{
	m_player = new PlayerEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_player->SetPos(sf::Vector2f(50.0f, 50.0f));  // <-- Move its initial position
	m_player->SetSize(sf::Vector2f(50.0f, 50.0f)); // <-- Make the square bigger

	GameEngine::RenderComponent* render = m_player->AddComponent<GameEngine::RenderComponent>(); // <-- Capturing the new component

	render->SetFillColor(sf::Color::Red); // <-- Change the fill color to Red
}

void GameBoard::CreateBackground() 
{

}