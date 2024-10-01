#pragma once
#include "config.h"

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <sgg/graphics.h>


#include <string>
#include <string>
#include <vector> 

class GameState
{
	//for the different status of the game
	typedef enum { STATUS_START, STATUS_GAMEOVER, STATUS_LEVEL1, STATUS_LEVEL2, STATUS_LEVEL3 } status;
	
private:
	static GameState* m_unique_instance;
	status m_current_status = STATUS_START;

		
	class Level * m_current_level = 0;
	class Player* m_player = 0;
	void drawEndScreen();

	
	GameState();

public:
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;
	
	bool m_debugging = false;

	//member variables for game over handling
	bool m_game_start = true;
	bool m_game_over = false;
	graphics::Brush m_brush_game_start; //brush for game start text
	graphics::Brush textBrush;
	graphics::Brush m_brush_game_over; // Brush for game-over text


public:
	~GameState();
	static GameState* getInstance();

	bool init();
	void draw();
	void update(float dt);

	status getCurrentStatus() const {
        return m_current_status;
    }


	// function to handle game over
	void endGame();

	std::string getFullAssetPath(const std::string& asset);
	std::string getAssetDir();

	float getCanvasWidth() { return CANVAS_WIDTH; }
	float getCanvasHeight() { return CANVAS_HEIGHT; }

	
	

	class Player* getPlayer() { return m_player; }

};
#endif 