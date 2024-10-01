#include "gamestate.h"

#include <thread>
#include <chrono>
#include <iostream>

#include "level.h"
#include "player.h"
using namespace std::chrono_literals;

GameState::GameState()
{
}

GameState::~GameState()
{
	if (m_current_level)
		delete m_current_level;
	if (m_player)
		delete m_player;
}

GameState* GameState::getInstance()
{
	if (!m_unique_instance)
	{
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}

bool GameState::init()
{
	
	
		graphics::playMusic(getFullAssetPath("soundtro.wav"), 1.0f, true, 600);
	
		graphics::preloadBitmaps(getAssetDir());
		graphics::setFont(std::string(ASSET_PATH) + "nulshockbd.otf");
		//try to print in screen the word SCORE

		float posX = 20.0f; 
		float posY = 20.0f;
		float textSize = 20.0f; 
		graphics::Brush brush;
		m_brush_game_start.fill_color[0] = 1.0f;
		m_brush_game_start.fill_color[1] = 0.0f;
		m_brush_game_start.fill_color[2] = 0.0f;
		brush.fill_opacity = 1.0f; //opaque
		graphics::drawText(posX, posY, textSize, "” œ—", brush);

		//do the nesecary actions based on the status
		switch (m_current_status) {
		case STATUS_START:
			std::cout << "status start it is\n ";

			m_current_level = new Level(this, m_current_status);
			break;
		case STATUS_GAMEOVER:

			m_current_level = new Level(this, m_current_status);
			std::cout << "status game over it is\n";

			break;
		case STATUS_LEVEL1:
			// Load level 1
			m_current_level = new Level(this, m_current_status);
			std::cout << "STATUS LEVEL 1 IT IS\n";

			break;
		case STATUS_LEVEL2:
			// Load level 2
			m_current_level = new Level(this, m_current_status);
			break;
		case STATUS_LEVEL3:
			//Load level 3
			m_current_level = new Level(this, m_current_status);
		}


		m_current_level->init();

		m_player = new Player("Player");
		m_player->init();
		int m_score = 0;
		m_game_start = true;

		return true;
	
}

void GameState::draw()
{


	if (!m_current_level)
		return;

	m_current_level->draw();

	switch (m_current_status) {
	case STATUS_START:
		if (graphics::getKeyState(graphics::SCANCODE_RETURN))
		{
			m_current_status = STATUS_LEVEL1;
			m_game_start = false; // Start the game when Enter is pressed
		}
		break;
		// Draw game over screen
	case STATUS_GAMEOVER:
		drawEndScreen();
		m_current_status = STATUS_GAMEOVER;

		break;
	case STATUS_LEVEL1:
		m_player->draw();
		break;
	case STATUS_LEVEL2:
		m_player->draw();
		break;
	case STATUS_LEVEL3:
		m_player->draw();
		break;
	}

}

void GameState::update(float dt)
{

	// Skip an update if a long delay is detected 
	// to avoid messing up the collision simulation
	if (dt > 500) // ms
		return;

	// Avoid too quick updates
	float sleep_time = std::max(17.0f - dt, 0.0f);
	if (sleep_time > 0.0f)
	{
		std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
	}
	switch (m_current_status) {
	case STATUS_START:
		if (graphics::getKeyState(graphics::SCANCODE_RETURN))
		{
			m_current_status = STATUS_LEVEL1;
			m_game_start = false; // Start the game when Enter is pressed
			init();
		}
		break;

	}
	

	if (!m_game_over && m_current_status>0)
	{
		m_current_level->update(dt);
		m_player->update(dt);

		// Check if the penguin has fallen and trigger game over 
		if (m_player->getPosY() > 20) {
			std::cout << "You lost, Iceskater fell below -1.0f. Ending game." << std::endl;
			drawEndScreen();
			m_current_status = STATUS_GAMEOVER;
			
			endGame();

		}
	}

	if (!m_current_level)
		return;

	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);


}



void GameState::drawEndScreen() {
	m_brush_game_over.texture = this->getFullAssetPath("background3.png");
	graphics::drawRect(this->getCanvasWidth() * 0.5f, this->getCanvasHeight() * 0.5f, 6.0f, 6.0f, m_brush_game_over);
	return;
	
}

void GameState::endGame()
{
	m_game_over = true;
	m_current_status = STATUS_GAMEOVER;
	std::cout << "Game Over!" << std::endl;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return ASSET_PATH + asset;
}

std::string GameState::getAssetDir()
{
	return ASSET_PATH;
}

GameState* GameState::m_unique_instance = nullptr;