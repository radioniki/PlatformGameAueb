#include "igloo.h"
#include <sgg/graphics.h>

Igloo::Igloo(const std::string& name, float x, float y, float w, float h) : GameObject(name), m_pos_x(x), m_pos_y(y), iglooBox(x, y, w, h)
{
    iglooBrush = new graphics::Brush();
}





bool Igloo::collidesWithPlayer(const Player& player) const {
    return iglooBox.intersect(player.getBoundingBox());

}