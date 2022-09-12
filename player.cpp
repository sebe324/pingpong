#include "player.h"
#include <iostream>
Player::Player(int x, int y, int w, int h, unsigned int c, int btn1, int btn2) : Entity(x,y,w,h,c){
score=0;
btnUp=btn1;
btnDown=btn2;
}
Player::Player(int x, int y, int w, int h, unsigned int c, int s) : Entity(x,y,w,h,c){
score=s;
}
Player::Player() : Entity(){}
void Player::setScore(int s){
score=s;
}
int Player::getScore(){
return score;
}
void Player::setBtnUp(int btn){
btnUp=btn;
}
int Player::getBtnUp(){
return btnUp;
}
void Player::setBtnDown(int btn){
btnDown=btn;
}
int Player::getBtnDown(){
return btnDown;
}
void Player::incScore(){
score++;
}
