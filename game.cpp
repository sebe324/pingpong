#include "game.h"
#include "renderer.h"
#include "utils.h"
#include "platformCommon.h"
#include <cstdlib>
#include <iostream>
/*float player1Pos=0.35, player1Vel, player2Pos=0.35, player2Vel; //player position and player velocity
float speed=1;
int player1Score=0, player2Score=0;
const float playerHeight=0.25, playerWidth=0.05;
float ballPX=0.4, ballPY=0.4, ballVelX=0.55, ballVelY;
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
        if(ballPX>0.8 && ballPX<0.85 && ballPY+0.05>=player2Pos && ballPY<=player2Pos+playerHeight){ballVelX*=-1; ballVelY=player2Vel*0.4+((ballPY-player2Pos)/playerHeight*0.3);}
        if(ballPX<0.15&& ballPX>0.1&&ballPY+0.05>=player1Pos && ballPY<=player1Pos+playerHeight){ballVelX*=-1;  ballVelY=player1Vel*0.4+((ballPY-player1Pos)/playerHeight*0.3);}
        if(ballPY>0.9||ballPY<0.05) ballVelY*=-1;
        if(ballPX>0.9){
            ballVelX=-0.55;
            ballVelY=0;
            ballPX=0.4;
            ballPY=0.4;
            player1Score++;
        }
           if(ballPX<0){
            ballVelX=0.55;
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
        renderer->drawNumber((int)1/deltaTime,0.07,0.955,0.008,0xffffff);
}*/
Game::Game(int x, int y, int w, int h, unsigned int c, Player p[2], Ball b) : Entity(x,y,w,h,c){
player[0]=p[0];
player[1]=p[1];
ball=b;
deltaTime=0;
}
void Game::simulateGame(Input* input, float dt){
    deltaTime=dt;
    if(isDown(BUTTON_P1UP)) player[0].moveVertical(650*deltaTime);
    if(isDown(BUTTON_P1DOWN)) player[0].moveVertical(-650*deltaTime);
    if(isDown(BUTTON_P2UP)) player[1].moveVertical(650*deltaTime);
    if(isDown(BUTTON_P2DOWN)) player[1].moveVertical(-650*deltaTime);
    ball.setPosX(ball.getVelX()*deltaTime+ball.getPosX());
    ball.setPosY(ball.getVelY()*deltaTime+ball.getPosY());
for(int i=0; i<2; i++){
if(player[i].getPosY()+player[i].getHeight()>height) player[i].setPosY(height-player[i].getHeight());
else if(player[i].getPosY()<0) player[i].setPosY(0);
if(ball.didCollide(player[i])){
    ball.setPosX(Utils::isPositive(ball.getPosX()-player[i].getPosX())*10+ball.getPosX());
    ball.setVelY(500*ball.getBounce()*Utils::isPositive(ball.getPosY()-(player[i].getPosY()+player[i].getHeight()/2))*1.03);
    ball.setVelX(ball.getVelX()*-1.03);
}
}
if(ball.getPosY()<=0 || ball.getPosY()+ball.getHeight()>=height){ball.setPosY(ball.getPosY()-2*Utils::isPositive(ball.getPosY()-posY)); ball.setVelY(ball.getVelY()*-1);}
if(ball.getPosX()<0){
ball.setVelY(0);
ball.setVelX(450);
ball.setPosX((width-30)/2);
ball.setPosY((height-30)/2);
player[1].incScore();
}
else if(ball.getPosX()+ball.getWidth()>width){
    ball.setVelY(0);
ball.setVelX(-450);
ball.setPosX((width-30)/2);
ball.setPosY((height-30)/2);
player[0].incScore();
}

}
void Game::renderGame(Renderer *renderer){
renderer->drawRectangle(posX,posY,width,height,color);
renderer->drawRectangle(posX+(width-20)/2,posY, 20,height,0x929ea3);
renderer->drawRectangle(posX+ball.getPosX(), posY+ball.getPosY(), ball.getWidth(), ball.getHeight(), ball.getColor());
for(int i=0; i<2; i++) renderer->drawRectangle(posX+player[i].getPosX(),posY+player[i].getPosY(),player[i].getWidth(),player[i].getHeight(),player[i].getColor());
renderer->drawNumber(player[0].getScore(),posX-100,posY+(height-75)/2,15,player[0].getColor());
renderer->drawNumber(player[1].getScore(),posX+width+100,posY+(height-75)/2,15,player[1].getColor());
renderer->drawNumber(1/deltaTime, renderer->getWidth()-40, renderer->getHeight()-30, 5, 0xffffff);
}
