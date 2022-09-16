#include "entity.h"
Entity::Entity(float x, float y, int w, int h, unsigned int c){
    posX=x;
    posY=y;
    width=w;
    height=h;
    color=c;
}
Entity::Entity(){}
void Entity::setPosX(float x){
posX=x;
}
float Entity::getPosX(){
return posX;
}
void Entity::setPosY(float y){
posY=y;
}
float Entity::getPosY(){
return posY;
}
void Entity::setWidth(int w){
width=w;
}
int Entity::getWidth(){
return width;
}
void Entity::setHeight(int h){
height=h;
}
int Entity::getHeight(){
return height;
}
void Entity::setColor(unsigned int c){
color=c;
}
unsigned int Entity::getColor(){
return color;
}
bool Entity::didCollide(Entity entity){
    if(entity.getPosX()<posX+width&&
       entity.getPosX()+entity.getWidth()>posX&&
       entity.getPosY()<posY+height&&
       entity.getPosY()+entity.getHeight()>posY
       ) return true;
    else return false;
}
bool Entity::isInside(Entity entity){
    if(posX+width<entity.getPosX()+entity.getWidth() &&
       posX>entity.getPosX() &&
       posY+height<entity.getPosY()+entity.getHeight() &&
       posY>entity.getPosY()
       ) return true;
        else return false;
}
void Entity::moveHorizontal(float amount){
posX+=amount;
}
void Entity::moveVertical(float amount){
posY+=amount;
}
void Entity::stayInside(Entity entity){
if(posX+width>entity.getPosX()+entity.getWidth())posX=entity.getPosX()+entity.getWidth()-width;
       else if(posX<entity.getPosX())posX=entity.getPosX();
       if(posY+height>entity.getPosY()+entity.getHeight()) posY=entity.getPosY()+entity.getHeight()-height;
       else if(posY<entity.getPosY()) posY=entity.getPosY();
}
