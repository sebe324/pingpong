#ifndef GAME_H
#define GAME_H
#include "platformCommon.h"
#include "renderer.h"
#include "windows.h"
#include "player.h"
#include "ball.h"
#include "entity.h"
#define isDown(b) input->buttons[b].isDown
#define pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define released(b) (!input->buttons[b].isDown && input->buttons[b].changed)
class Game : public Entity{
    private:
        Player player[2];
        Ball ball;
        float deltaTime;
        bool ai;
        bool paused;
        bool isRunning;
        Entity border[2];
    public:
        Game(int x, int y, int w, int h, unsigned int c, Player p[2], Ball b, bool a);
        void getInput(Input* input, HWND hwnd);
        void simulateGame();
        void renderGame(Renderer *renderer);
        bool getPaused();
        void setPaused(bool p);
        void setDeltaTime(float dt);
        void exitGame(HWND hwnd);
        bool getIsRunning();
        void setIsRunning(bool r);
};

#endif
