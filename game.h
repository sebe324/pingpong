#ifndef GAME_H
#define GAME_H
#include "platformCommon.h"
#include "renderer.h"

#define isDown(b) input->buttons[b].isDown
#define pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define released(b) (!input->buttons[b].isDown && input->buttons[b].changed)

void simulateGame(Input* input, Renderer* renderer,float deltaTime);
#endif
