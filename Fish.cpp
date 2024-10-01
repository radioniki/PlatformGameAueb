#pragma once

#include "Fish.h"
#include <sgg/graphics.h>


Fish::Fish(const std::string& name,float x, float y, float w, float h): GameObject(name), m_pos_x(x), m_pos_y(y), fishBox(x, y, w, h), m_isActive(true)
{
    fishBrush = new graphics::Brush();
}

void Fish::catchFish() {
    m_isActive = false;
}

bool Fish::isActive() const {
    return m_isActive;
}

bool Fish::collidesWithPlayer(const Player& player) const {
    return fishBox.intersect(player.getBoundingBox());

}

void Fish::setActive(bool active) {
    m_isActive = active;
}

void Fish::draw() {
    if (m_isActive) {
        graphics::drawRect(fishBox.m_pos_x, fishBox.m_pos_y, fishBox.m_width, fishBox.m_height, *fishBrush);
    }
}

void Fish::update(float dt) {
    
}






Fish::~Fish() {}