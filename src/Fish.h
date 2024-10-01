// Fish.h
#pragma once
#include <sgg/graphics.h>
#include "player.h"
#include "gameobject.h" 




class Player;

namespace graphics {
    struct Brush;  // Forward declaration of Brush
}

class Fish : public GameObject
{
    private:
    Box fishBox;
    bool m_isActive; // Indicates whether the fish is active or caught
    graphics::Brush* fishBrush;  // Pointer to Brush
    float m_pos_x;   
    float m_pos_y;


    public:
    Fish(const std::string& name,float x, float y, float w, float h);
    bool collidesWithPlayer(const Player& player) const;
    void catchFish(); // the fish is caught
    bool isActive() const;
    void setActive(bool active);
    void draw() override;
    void update(float dt) override;

    float getPositionX() const { return m_pos_x; }
    float getPositionY() const { return m_pos_y; }
    graphics::Brush* getFishBrush() const {
        return fishBrush;
    }
    

    ~Fish();
};

