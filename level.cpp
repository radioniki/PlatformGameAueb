#include "level.h"
#include <sgg/graphics.h>
#include "util.h"
#include <iostream>
#include <fstream>




void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	std::string& name = m_block_names[i];

	
	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;

	m_block_brush.texture = m_state->getFullAssetPath(name);

	graphics::drawRect(x, y, 1.8f * m_block_size, 1.8f * m_block_size, m_block_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);

}

void Level::drawFish(int i)
{
	Fish& fish = m_fishes[i];
	std::string& name = m_fish_names[i];


	float x = fish.getPositionX() + m_state->m_global_offset_x;
	float y = fish.getPositionY() + m_state->m_global_offset_y;

	fishBrush.texture = m_state->getFullAssetPath(name);

	graphics::drawRect(x, y, 1.8f * m_fish_size, 1.8f * m_fish_size, fishBrush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_fish_size, m_fish_size, fishBrush_debug);

}

void Level::drawIgloo(int i)
{
	Igloo& igloo = m_igloo[i];
	std::string& name = m_igloo_name[i];

	float x = igloo.getPositionX() + m_state->m_global_offset_x;
	float y = igloo.getPositionY() + m_state->m_global_offset_y;

	m_igloo_brush.texture = m_state->getFullAssetPath(name);

	graphics::drawRect(x, y, 1.8f * m_igloo_size, 1.8f * m_igloo_size, m_igloo_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_igloo_size, m_igloo_size, m_igloo_brush_debug);



}



void Level::checkCollisions()
{

	for (auto& box : m_blocks)
	{
		if (m_state->getPlayer()->intersect(box))
			printf("*");
	}


	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(block))
		{
			printf("1");

			m_state->getPlayer()->m_pos_y += offset;

			// add sound event
			if (m_state->getPlayer()->m_vy > 1.0f)
				graphics::playSound(m_state->getFullAssetPath("jumpingice.wav"), 1.0f);

			m_state->getPlayer()->m_vy = 0.0f;

			break;
		}
	}

	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(block))
		{
			m_state->getPlayer()->m_pos_x += offset;

			m_state->getPlayer()->m_vx = 0.0f;
			break;
		}

	}
	//prevent penguin to jump through obstacles when jumping
	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectUp(block))
		{
			// If the penguin is jumping and collides with a block from below, adjust its position
			if (m_state->getPlayer()->m_vy < 0.0f)
			{
				m_state->getPlayer()->m_pos_y += offset;
				m_state->getPlayer()->m_vy = 0.0f;
			}
			break;
		}
	}

	// Iterate over fishes to check collisions with the player
	for (auto& fish : m_fishes) {
		if (fish.isActive() && fish.collidesWithPlayer(*m_state->getPlayer())) {
			fish.catchFish(); // Mark the fish as inactive
			//sound effect
			graphics::playSound(m_state->getFullAssetPath("fisheating.wav"), 1.0f);

		}
	}
	//cheking collision with igloo and changes to the next level
	for (auto& igloo : m_igloo) 
	{
		if (igloo.collidesWithPlayer(*m_state->getPlayer()))
		{
			if (m_status == 2) 
			{
				std::cout << "hit the igloo\n ";
				m_status = 3;
				graphics::playSound(m_state->getFullAssetPath("levelchangin.wav"), 1.0f);

				init();
			}
			else if (m_status == 3) 
			{
				m_status = 4;
				graphics::playSound(m_state->getFullAssetPath("levelchangin.wav"), 1.0f);

				init();
			}
			else if (m_status == 4)
			{
				m_status = 1;
				init();
			

			}
		}
	}
}


	


void Level::loadMap_foricecubes(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Error: Could not open the map file: " << filename << std::endl;
		return;
	}

	m_blocks.clear();
	m_block_names.clear();

	std::string line;
	int y = 0;

	while (std::getline(file, line))
	{
		for (int x = 0; x < line.size(); x++)
		{
			if (line[x] == 'X') // Assuming 'X' represents a block
			{
				m_blocks.push_back(Box(x, y, 1, 1));  // Create a block at position (x, y)
				m_block_names.push_back("icecube1.png");
			}
		}

	    y++;
	}

	file.close();
}
	


	


void Level::update(float dt)
{
	if (m_status >= 2)
	{
		if (m_state->getPlayer()->isActive())
			m_state->getPlayer()->update(dt);
	}
	
	checkCollisions();

	

	GameObject::update(dt);

}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();
	
	
	if (m_status >= 2)
	{
		float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
		float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;

		//draw background
		m_brush_background.texture = m_state->getFullAssetPath("startscreen.png");
		graphics::drawRect(offset_x, offset_y, 2.0f * w, 4.0f * w, m_brush_background);

		// draw player
		if (m_state->getPlayer()->isActive())
			m_state->getPlayer()->draw();

		// draw blocks
		for (int i = 0; i < m_blocks.size(); i++)
		{
			drawBlock(i);
		}

		//draw fishes
		for (int i = 0; i < m_fishes.size(); i++) {
			if (m_fishes[i].isActive()) {
				drawFish(i);
			}
		}

		//draw igloo
		for (int i = 0; i < m_igloo.size(); i++) {
			drawIgloo(i);
		}
	}
	else if (m_status == 0)
	{
		m_brush_background.texture = m_state->getFullAssetPath("background1.png");
		graphics::drawRect(w * 0.5f, h * 0.5f, 6.0f, 6.0f, m_brush_background);

	}
	else if (m_status == 1)

	{
		m_brush_background.texture = m_state->getFullAssetPath("startscreen.png");
		graphics::drawRect(w * 0.5f, h * 0.5f, 6.0f, 6.0f, m_brush_background);

	}

}

void Level::init()
{
	if (m_status >= 2)
	{
		// Stage 1
		for (auto p_gob : m_static_objects)
			if (p_gob) p_gob->init();

		for (auto p_gob : m_dynamic_objects)
			if (p_gob) p_gob->init();

		if (m_status == 3) {
			loadMap_foricecubes("level2_map.txt");
			loadMap_forfishes("position2_fishes.txt");
			loadMap_forigloo("position2_igloo.txt");
		}
		else if (m_status == 4)
		{
			loadMap_foricecubes("level3_map.txt");
			loadMap_forfishes("position3_fishes.txt");
			loadMap_forigloo("position_igloo.txt");
		}
		else {
			loadMap_foricecubes("level_map.txt");
			loadMap_forfishes("position_fishes.txt");
			loadMap_forigloo("position_igloo.txt");
		}


		m_block_brush.outline_opacity = 0.0f;
		m_block_brush_debug.fill_opacity = 0.1f;

		fishBrush.outline_opacity = 0.0f;
		fishBrush_debug.fill_opacity = 0.0f;

		m_igloo_brush.outline_opacity = 0.0f;
		m_igloo_brush_debug.fill_opacity = 0.0f;

		SETCOLOR(fishBrush_debug.fill_color, 0.1f, 1.0f, 0.1f);
		SETCOLOR(fishBrush_debug.outline_color, 0.3f, 1.0f, 0.2f);

		SETCOLOR(m_block_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
		SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);

		SETCOLOR(m_igloo_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
		SETCOLOR(m_igloo_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);
	}
	
}

Level::Level(GameState* state, const int status) : m_state(state), m_status(status) 
	{
	m_brush_background.outline_opacity = 0.0f;

	//m_status = status;
	switch (m_status)
	{
	case 0:
		m_brush_background.texture = m_state->getFullAssetPath("background1.png");
		break;
	case 1:
		m_brush_background.texture = m_state->getFullAssetPath("startscreen.png");
		break;
	case 2:
		m_brush_background.texture = m_state->getFullAssetPath("startscreen.png");
		break;
	case 3: 
		m_brush_background.texture = m_state->getFullAssetPath("startscreen.png");
		break;
	case 4:
		m_brush_background.texture = m_state->getFullAssetPath("startscreen.png");
		break;
		


	}


}

Level::~Level()
{
	for (auto p_go : m_static_objects)
		delete p_go;
	for (auto p_go : m_dynamic_objects)
		delete p_go;
}


void Level::loadMap_forfishes(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Error: Could not open the map file: " << filename << std::endl;
		return;
	}

	m_fishes.clear();
	m_fish_names.clear();

	std::string line;
	int y = 0;

	while (std::getline(file, line))
	{
		for (int x = 0; x < line.size(); ++x)
		{
			if (line[x] == 'f') // Assuming 'f' represents a fish
			{
				m_fishes.push_back(Fish("MyFish",x, y, 1, 1));  // Create a fish at position (x, y)
				m_fish_names.push_back("fish.png");
			}
		}

		++y;
	}

	file.close();
}

void Level::loadMap_forigloo(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open the igloo map file: " << filename << std::endl;
		return;
	}

	m_igloo.clear(); // Clear existing igloos
	m_igloo_name.clear();

	std::string line;
	int y = 0;

	while (std::getline(file, line)) {
		for (int x = 0; x < line.size(); ++x) {
			if (line[x] == 'i') { // Assuming 'i' represents an igloo
				m_igloo.push_back(Igloo("my igloo", x, y, 1, 1)); // Create an igloo at position (x, y)
				if (m_status == 3)
					m_igloo_name.push_back("igloo2.png");
				else
					m_igloo_name.push_back("igloo.png");

			}
		}
		++y;
	}

	file.close();
}





