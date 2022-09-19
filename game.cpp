#include "game.h"
#include "renderer.h"
#include "utils.h"
#include "platformCommon.h"
#include <cstdlib>
#include <iostream>
#include <windows.h>
Game::Game(int x, int y, int w, int h, unsigned int c, Player p[2], Ball b, bool a) : Entity(x,y,w,h,c){
player[0]=p[0];
player[1]=p[1];
ball=b;
deltaTime=0;
ai=a;
paused=false;
isRunning=true;
Entity border1(0,0,width*0.15, height, 0x487594);
Entity border2(width*0.85,0,width*0.15, height, 0x796265);
border[0]=border1;
border[1]=border2;
Entity ga(0,0,width,height,0);
gameArea=ga;
}
void Game::setDeltaTime(float dt){
  deltaTime=dt;
}
void Game::getInput(Input* input, HWND hwnd){
    if(!paused){
    if(isDown(BUTTON_P1UP)) player[0].moveVertical(player[0].getVelocity()*deltaTime);
    if(isDown(BUTTON_P1DOWN)) player[0].moveVertical(-player[0].getVelocity()*deltaTime);
    if(isDown(BUTTON_P1LEFT)) player[0].moveHorizontal(-player[0].getVelocity()*deltaTime*0.5);
    if(isDown(BUTTON_P1RIGHT)) player[0].moveHorizontal(player[0].getVelocity()*deltaTime*0.5);
    if(ai==false){
    if(isDown(BUTTON_P2UP)) player[1].moveVertical(player[1].getVelocity()*deltaTime);
    if(isDown(BUTTON_P2DOWN)) player[1].moveVertical(-player[1].getVelocity()*deltaTime);
    if(isDown(BUTTON_P2LEFT)) player[1].moveHorizontal(-player[1].getVelocity()*deltaTime*0.5);
    if(isDown(BUTTON_P2RIGHT)) player[1].moveHorizontal(player[1].getVelocity()*deltaTime*0.5);
    }
    else{
          if(player[1].getPosY()+(player[1].getHeight()/2)>ball.getPosY()&&ball.getPosX()>width/2) player[1].moveVertical(-player[1].getVelocity()*deltaTime*0.55);
        else if(player[1].getPosY()+(player[1].getHeight()/2)<ball.getPosY()&&ball.getPosX()>width/2)player[1].moveVertical(player[1].getVelocity()*deltaTime*0.55);
    }
    if(isDown(BUTTON_MODE1)) ai=false;
    if(isDown(BUTTON_MODE2)) ai=true;
    }
    if(isDown(BUTTON_PAUSE)) {isDown(BUTTON_PAUSE)=false; paused=!paused; PlaySound(TEXT("sounds\\pause.wav"), NULL, SND_ASYNC);

    if(player[1].getScore()==15 || player[0].getScore()==15){
        player[0].setScore(0);
        player[1].setScore(0);
        ball.setVelX(450);
    }
    }
    if(isDown(BUTTON_EXIT)) {exitGame(hwnd); isDown(BUTTON_EXIT)=false;}
    }

void Game::simulateGame(){
    ball.setPosX(ball.getVelX()*deltaTime+ball.getPosX());
    ball.setPosY(ball.getVelY()*deltaTime+ball.getPosY());
for(int i=0; i<2; i++){
player[i].stayInside(border[i]);
if(ball.didCollide(player[i])){
        PlaySound(TEXT("sounds\\pop.wav"), NULL, SND_ASYNC);
    ball.setPosX(Utils::isPositive(ball.getPosX()-player[i].getPosX())*10+ball.getPosX());
    ball.setVelY(500*ball.getBounce()*Utils::isPositive(ball.getPosY()-(player[i].getPosY()+player[i].getHeight()/2)));
    ball.setVelX(ball.getVelX()*-ball.getBounce());
}
}
if(ball.getPosY()<=0 || ball.getPosY()+ball.getHeight()>=height){
        //ball.setPosY(ball.getPosY()-(abs(Utils::clamp(0,ball.getPosY(), height)-ball.getPosY()))*Utils::isPositive(ball.getPosY()+ball.getHeight()-posY));
        ball.stayInside(gameArea);
ball.setVelY(ball.getVelY()*-1);
PlaySound(TEXT("sounds\\pop.wav"), NULL, SND_ASYNC);
}
if(ball.getPosX()<0){
ball.setVelY(0);
ball.setVelX(450);
ball.setPosX((width-30)/2);
ball.setPosY((height-30)/2);
PlaySound(TEXT("sounds\\point.wav"), NULL, SND_ASYNC);
player[1].incScore();
}
else if(ball.getPosX()+ball.getWidth()>width){
    ball.setVelY(0);
ball.setVelX(-450);
ball.setPosX((width-30)/2);
ball.setPosY((height-30)/2);
PlaySound(TEXT("sounds\\point.wav"), NULL, SND_ASYNC);
player[0].incScore();

}

}
void Game::renderGame(Renderer *renderer){
//renderer->drawBackground(0x2d3436);
renderer->drawBackground2(posX, posY,width,height,0x2d3436);
renderer->drawRectangle(posX,posY,width,height,color);
renderer->drawRectangle(posX+(width-20)/2,posY, 20,height,0x929ea3);
for(int i=0; i<2; i++){ renderer->drawRectangle(posX+border[i].getPosX(), posY+border[i].getPosY(), border[i].getWidth(), border[i].getHeight(), border[i].getColor());
        renderer->drawRectangle(posX+player[i].getPosX(),posY+player[i].getPosY(),player[i].getWidth(),player[i].getHeight(),player[i].getColor());
        renderer->drawBorder(posX+player[i].getPosX(), posY+player[i].getPosY(), player[i].getWidth(), player[i].getHeight(),5 ,0x101010);
}
renderer->drawRectangle(posX+ball.getPosX(), posY+ball.getPosY(), ball.getWidth(), ball.getHeight(), ball.getColor());
renderer->drawNumber(player[0].getScore(),posX-100,posY+(height-75)/2,15,player[0].getColor());
renderer->drawNumber(player[1].getScore(),posX+width+100,posY+(height-75)/2,15,player[1].getColor());
renderer->drawNumber(1/deltaTime, renderer->getWidth()-40, renderer->getHeight()-30, 5, 0xffffff);
renderer->drawText("version 1.4.2",(0),renderer->getHeight()-20,3,0xffffff);
renderer->drawText("ping pong",(renderer->getWidth()-270)/2,renderer->getHeight()-50,5,0xffffff);
renderer->drawText("player one",posX+(width/2-150)/2-60, posY-50, 5, player[0].getColor());
renderer->drawText("player two",(width/2+posX+posX+width-150)/2-60, posY-50, 5, player[1].getColor());
if(player[0].getScore()==15){
        ball.setVelX(0);
    ball.setVelY(0);
    renderer->drawText("player one wins. p to restart",posX,renderer->getHeight()/2,5,0xfdcb6e);
    setPaused(true);
}
else if(player[1].getScore()==15){
    ball.setVelX(0);
    ball.setVelY(0);
    renderer->drawText("player two wins. p to restart",posX,renderer->getHeight()/2,5,0xfdcb6e);
    setPaused(true);
}
}
bool Game::getPaused(){
return paused;
}
void Game::setPaused(bool p){
paused=p;
}
void Game::exitGame(HWND hwnd){
    paused=true;
            PlaySound(TEXT("sounds\\pause.wav"), NULL, SND_ASYNC);
            if(MessageBox(hwnd, "Do you want to exit the game?", "Goodbye",MB_OKCANCEL | MB_ICONQUESTION)==1){
                     PlaySound(TEXT("sounds\\close.wav"), NULL, SND_ASYNC);
                      isRunning=false;
            }else{
            PlaySound(TEXT("sounds\\pause.wav"), NULL, SND_SYNC);
            paused=false;
            }
}
bool Game::getIsRunning(){
return isRunning;
}
void Game::setIsRunning(bool r){
isRunning=r;
}
