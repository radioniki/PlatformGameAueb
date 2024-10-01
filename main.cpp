#include <sgg/graphics.h>
#include "config.h"
#include <iostream>

#include "gamestate.h"

void draw()
{
    GameState* mygamestate = reinterpret_cast<GameState*>(graphics::getUserData());
    mygamestate->draw();
}
void update(float dt)
{
    GameState* mygamestate = reinterpret_cast<GameState*>(graphics::getUserData());
    mygamestate->update(dt);
}

int main(int argc, char** argv)
{
    graphics::createWindow(800, 800, "icepenguin");
    GameState* mygamestate = GameState::getInstance();
    GameState::getInstance()->init();
    graphics::setUserData(GameState::getInstance());

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    
    graphics::setFont(std::string(ASSET_PATH) + "nulshockbd.otf");

    //start main game message loop
    graphics::startMessageLoop();

    // when game ends or ESC is pressed or X is clicked then destroy everything : D
        graphics::destroyWindow();
	return 0;
}

