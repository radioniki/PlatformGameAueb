#pragma once

#include "Level2.h"
#include <iostream>
#include <fstream>




Level2::Level2(const std::string& name)
	: Level(name) {
	// Additional initialization for Level 2, if any
}

Level2::~Level2() {
    // Destructor implementation (if needed)
}

void Level2::init() {

	Level::init();


	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();

	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();

	loadMap_foricecubes("level2_map.txt");
	loadMap_forfishes("position_fishes.txt");
}

void Level2::update(float dt) {
    // Update logic specific to Level 2
    // Handle collisions, update game state, etc.
}


void Level2::draw() {
    Level::draw();

}

void Level2::loadMap_foricecubes(const std::string& filename)
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
		for (int x = 0; x < line.size(); ++x)
		{
			if (line[x] == 'X') // Assuming 'X' represents a block
			{
				m_blocks.push_back(Box(x, y, 1, 1));  // Create a block at position (x, y)
				m_block_names.push_back("icecube1.png");
			}
		}

		++y;
	}

	file.close();
}
