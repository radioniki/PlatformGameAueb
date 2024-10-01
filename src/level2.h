
#pragma once

#include "gameobject.h"

#include "Level.h" 


class Level2 : public Level {
public:
    Level2(const std::string& name);
    ~Level2();  // Destructor
    void init() override;  // Initialization function for Level 2
    void update(float dt) override;  // Update function for Level 2
    void draw() override;  // Draw function for Level 2
    void loadMap_foricecubes(const std::string& filename) override;
    //void loadMap_forfishes(const std::string& filename) override;
    //void changelevel() override;


};


