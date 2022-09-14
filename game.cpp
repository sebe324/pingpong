#include "game.h"
#include "renderer.h"
#include "utils.h"
#include "platformCommon.h"
#include <cstdlib>
#include <iostream>
Game::Game(int x, int y, int w, int h, unsigned int c, Player p[2], Ball b, bool a) : Entity(x,y,w,h,c){
player[0]=p[0];
player[1]=p[1];
ball=b;
deltaTime=0;
ai=a;
paused=false;
}
void Game::setDeltaTime(float dt){
  deltaTime=dt;
}
void Game::getInput(Input* input){
    if(isDown(BUTTON_P1UP)) player[0].moveVertical(player[0].getVelocity()*deltaTime);
    if(isDown(BUTTON_P1DOWN)) player[0].moveVertical(-player[0].getVelocity()*deltaTime);
    if(ai==false){
    if(isDown(BUTTON_P2UP)) player[1].moveVertical(player[1].getVelocity()*deltaTime);
    if(isDown(BUTTON_P2DOWN)) player[1].moveVertical(-player[1].getVelocity()*deltaTime);
    }
    else{
        if(player[1].getPosY()+(player[1].getHeight()/2)>ball.getPosY()) player[1].moveVertical(-player[1].getVelocity()*deltaTime);
        else player[1].moveVertical(player[1].getVelocity()*deltaTime);
    }
    if(isDown(BUTTON_MODE1)) ai=false;
    if(isDown(BUTTON_MODE2)) ai=true;
    if(isDown(BUTTON_PAUSE)) {isDown(BUTTON_PAUSE)=false; paused=!paused;}
}
void Game::simulateGame(){
    ball.setPosX(ball.getVelX()*deltaTime+ball.getPosX());
    ball.setPosY(ball.getVelY()*deltaTime+ball.getPosY());
for(int i=0; i<2; i++){
if(player[i].getPosY()+player[i].getHeight()>height) player[i].setPosY(height-player[i].getHeight());
else if(player[i].getPosY()<0) player[i].setPosY(0);
if(ball.didCollide(player[i])){
    ball.setPosX(Utils::isPositive(ball.getPosX()-player[i].getPosX())*10+ball.getPosX());
    ball.setVelY(500*ball.getBounce()*Utils::isPositive(ball.getPosY()-(player[i].getPosY()+player[i].getHeight()/2)));
    ball.setVelX(ball.getVelX()*-ball.getBounce());
}
}
if(ball.getPosY()<=0 || ball.getPosY()+ball.getHeight()>=height){ball.setPosY(ball.getPosY()-10*Utils::isPositive(ball.getPosY()+ball.getHeight()-posY)); ball.setVelY(ball.getVelY()*-1);}
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
bool Game::getPaused(){
return paused;
}
