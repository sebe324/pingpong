#include "game.h"
#include "renderer.h"
#include "platformCommon.h"
#include <iostream>
float player1Pos=0.25, player1Velocity, player2Pos=0.25, player2Velocity; //player position and player velocity
float speed=1;
const float playerHeight=0.3, playerWidth=0.05;
void simulateGame(Input* input, Renderer* renderer, float deltaTime){
renderer->drawBackground(0x2d3436);
renderer->drawResponsiveRectangle(0.05,0.05,0.9,0.9,0x636e72);
float player1Acc = 0; //player acceleration
    if(isDown(BUTTON_W)) player1Acc+=5;
    if(isDown(BUTTON_S)) player1Acc-=5;
        player1Acc -= player1Velocity; //friction
        player1Pos=player1Pos+(player1Velocity*deltaTime)+(player1Acc*deltaTime*deltaTime*0.5);
        player1Velocity=player1Velocity+player1Acc*deltaTime;
        if(player1Pos>0.95-playerHeight) {player1Pos=0.95-playerHeight; player1Velocity*=-0.2;}
        else if(player1Pos<0.05){player1Pos=0.05; player1Velocity*=-0.2;}
        renderer->drawResponsiveRectangle(0.1,player1Pos,playerWidth,playerHeight,0xd63031);
        float player2Acc = 0; //player acceleration
    if(isDown(BUTTON_UP)) player2Acc+=5;
    if(isDown(BUTTON_DOWN)) player2Acc-=5;
        player2Acc -= player2Velocity; //friction
        player2Pos=player2Pos+(player2Velocity*deltaTime)+(player2Acc*deltaTime*deltaTime*0.5);
        player2Velocity=player2Velocity+player2Acc*deltaTime;
        if(player2Pos>0.95-playerHeight) {player2Pos=0.95-playerHeight; player2Velocity*=-0.2;}
        else if(player2Pos<0.05){player2Pos=0.05; player2Velocity*=-0.2;}
        renderer->drawResponsiveRectangle(0.8,player2Pos,playerWidth,playerHeight,0x0984e3);
}
