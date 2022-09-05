#include "game.h"
#include "renderer.h"
#include "platformCommon.h"
#include <cstdlib>
#include <iostream>
float player1Pos=0.35, player1Vel, player2Pos=0.35, player2Vel; //player position and player velocity
float speed=1;
int player1Score=0, player2Score=0;
const float playerHeight=0.25, playerWidth=0.05;
float ballPX=0.4, ballPY=0.4, ballVelX=0.45, ballVelY;
void simulateGame(Input* input, Renderer* renderer, float deltaTime){
renderer->drawBackground(0x2d3436);
renderer->drawResponsiveRectangle(0.05,0.05,0.9,0.9,0x636e72);
float player1Acc = 0; //player acceleration
    if(isDown(BUTTON_W)) player1Acc+=5;
    if(isDown(BUTTON_S)) player1Acc-=5;
        player1Acc -= player1Vel; //friction
        player1Pos=player1Pos+(player1Vel*deltaTime)+(player1Acc*deltaTime*deltaTime*0.5);
        player1Vel=player1Vel+player1Acc*deltaTime;
        if(player1Pos>0.95-playerHeight) {player1Pos=0.95-playerHeight; player1Vel*=-0.2;}
        else if(player1Pos<0.05){player1Pos=0.05; player1Vel*=-0.2;}

        float player2Acc = 0; //player acceleration
    if(isDown(BUTTON_UP)) player2Acc+=5;
    if(isDown(BUTTON_DOWN)) player2Acc-=5;
        player2Acc -= player2Vel; //friction
        player2Pos=player2Pos+(player2Vel*deltaTime)+(player2Acc*deltaTime*deltaTime*0.5);
        player2Vel=player2Vel+player2Acc*deltaTime;
        if(player2Pos>0.95-playerHeight) {player2Pos=0.95-playerHeight; player2Vel*=-0.2;}
        else if(player2Pos<0.05){player2Pos=0.05; player2Vel*=-0.2;}
        ballPX=ballPX+(ballVelX*deltaTime);
        ballPY=ballPY+(ballVelY*deltaTime);
        if(ballPX>0.8 && ballPX<0.9 && ballPY>=player2Pos && ballPY<=player2Pos+playerHeight){ballVelX*=-1; ballVelY=((std::rand()%5)-5)*0.1;}
        if(ballPX<0.15&& ballPX>0.1&&ballPY>=player1Pos && ballPY<=player1Pos+playerHeight){ballVelX*=-1;  ballVelY=((std::rand()%5)-5)*0.1*-1; std::cout << '\a';}
        if(ballPY>0.9||ballPY<0.05) ballVelY*=-1;
        if(ballPX>0.9){
            ballVelX=-0.45;
            ballVelY=0;
            ballPX=0.4;
            ballPY=0.4;
            player1Score++;
        }
           if(ballPX<0){
            ballVelX=0.45;
            ballVelY=0;
            ballPX=0.4;
            ballPY=0.4;
            player2Score++;
        }
        renderer->drawResponsiveRectangle(ballPX,ballPY,0.05,0.05, 0xffffff);
        renderer->drawResponsiveRectangle(0.1,player1Pos,playerWidth,playerHeight,0xd63031);
        renderer->drawResponsiveRectangle(0.85,player2Pos,playerWidth,playerHeight,0x0984e3);
        renderer->drawNumber(player1Score,1.5,0.2,0.03,0xd63031);
        renderer->drawNumber(player2Score,1.5,0.7,0.03,0x0984e3);
}
