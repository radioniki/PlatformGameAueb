#pragma once

#include "gameobject.h"

#include <vector>
#include <list>
#include "box.h"

#include <string>
#include <sgg/graphics.h>

#include "player.h"
#include "Fish.h"
#include "igloo.h"
#include "gamestate.h"






class Level : public GameObject
{
protected:
	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;

private:
	graphics::Brush m_brush_background;
	GameState* m_state;
	int m_status;

	const float m_block_size = 1.0f;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;

	const float m_fish_size = 0.3f;
	graphics::Brush fishBrush;
	graphics::Brush fishBrush_debug;

	const float m_igloo_size = 1.0f;
	graphics::Brush m_igloo_brush;
	graphics::Brush m_igloo_brush_debug;
	

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	// dedicated method to draw a block
	void drawBlock(int i);
	// dedicated method to draw a fish
	void drawFish(int i);
	//dedicated method to draw an igloo
	void drawIgloo(int i);



	// detect collisions
	void checkCollisions();



public:
	
	void update(float dt) override;
	void draw() override;
	void init() override;

	virtual void loadMap_foricecubes(const std::string& filename);
	virtual void loadMap_forfishes(const std::string& filename);
	virtual void loadMap_forigloo(const std::string& filename);



	// add some collidable blocks
	std::vector<Box> m_blocks;
	std::vector<std::string> m_block_names;
	//add fishes to the level
	std::vector<Fish> m_fishes;
	std::vector<std::string> m_fish_names;
	//add the igloo
	std::vector<Igloo> m_igloo;
	std::vector<std::string> m_igloo_name;

	

	Level(GameState* state, const int status);
	~Level() override;
};