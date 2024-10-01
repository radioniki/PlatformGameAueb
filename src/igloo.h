#pragma once

#include <sgg/graphics.h>
#include "gameobject.h"
#include "player.h"

namespace graphics {
    struct Brush;  // declaration of Brush
}


class Igloo : public GameObject {
public:
    Igloo(const std::string& name, float x, float y, float w, float h);
    bool collidesWithPlayer(const Player& player) const;


    float getPositionX() const { return m_pos_x; }
    float getPositionY() const { return m_pos_y; }
private:
    Box iglooBox;
    graphics::Brush* iglooBrush;  // Pointer to Brush
    float m_pos_x;
    float m_pos_y;



};
