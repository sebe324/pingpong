#include "renderer.h"
#include "utils.h"
Renderer::Renderer(void* m, int w, int h){
memory=m;
width=w;
height=h;
}

void Renderer::drawBackground(unsigned int color){
unsigned int* pixel = (unsigned int*)memory;
    for (int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            *pixel++=color;
        }
    }
}
void Renderer::drawRectangle(int x, int y, int recWidth, int recHeight, unsigned int color){
    int x1=x+recWidth;
    int y1=y+recHeight;
    x=Utils::clamp(0,x,width);
    y=Utils::clamp(0,y,height);
    x1=Utils::clamp(0,x1,width);
    y1=Utils::clamp(0,y1,height);
    for (int i=y; i<y1; i++){
unsigned int* pixel = (unsigned int*)memory+x+i*width; //starting pixel must be changed so it starts at rectangle x and moves as it renders another row
        for(int j=x; j<x1; j++){
            *pixel++=color;
        }
    }
}
void Renderer::drawResponsiveRectangle(float x, float y, float recWidth, float recHeight, unsigned int color){
    x=x*height;
    y=y*height;
    int x1=(x+recWidth)*height;
    int y1=(y+recHeight)*height;
    int x0=Utils::clamp(0,(int)x,width);
    int y0=Utils::clamp(0,(int)y,height);
     x1=Utils::clamp(0,(int)x1,width);
     y1=Utils::clamp(0,(int)y1,height);
    for (int i=y0; i<y1; i++){
unsigned int* pixel = (unsigned int*)memory+x0+i*width; //starting pixel must be changed so it starts at rectangle x and moves as it renders another row
        for(int j=x0; j<x1; j++){
            *pixel++=color;
        }
    }
}
void Renderer::drawNumber(int number, float x, float y, float nsize, unsigned int color){
   do{
            int digit=0;
            digit=number%10;
            number=number/10;
switch(digit){
    case 0:
    drawRectangle(x,y,nsize,nsize*5,color);
    drawRectangle(x+nsize*2,y,nsize,nsize*5,color);
    drawRectangle(x+nsize,y,nsize,nsize,color);
    drawRectangle(x+nsize,y+nsize*4,nsize,nsize,color);
     x-=nsize*4;
    break;
    case 1:
    drawRectangle(x+nsize*2,y,nsize,nsize*5,color);
    x-=nsize*4;
    break;
    case 2:
    drawRectangle(x,y, nsize*3, nsize, color);
    drawRectangle(x,y+nsize*2, nsize*3, nsize, color);
    drawRectangle(x,y+nsize*4, nsize*3, nsize, color);
    drawRectangle(x,y+nsize,nsize,nsize,color);
    drawRectangle(x+nsize*2,y+nsize*3,nsize,nsize,color);
     x-=nsize*4;
    break;
    case 3:
        drawRectangle(x,y+nsize*2, nsize*3, nsize, color);
        drawRectangle(x,y+nsize*4, nsize*3, nsize, color);
        drawRectangle(x,y, nsize*3, nsize, color);
        drawRectangle(x+nsize*2,y,nsize,nsize*4,color);
         x-=nsize*4;
    break;
    case 4:
        drawRectangle(x,y+nsize,nsize,nsize*3,color);
        drawRectangle(x+nsize,y+nsize,nsize,nsize,color);
        drawRectangle(x+nsize,y+nsize*4,nsize,nsize,color);
        drawRectangle(x+nsize*2,y,nsize,nsize*5,color);
         x-=nsize*4;
    break;
    case 5:
    drawRectangle(x,y, nsize*3, nsize, color);
    drawRectangle(x,y+nsize*2, nsize*3, nsize, color);
    drawRectangle(x,y+nsize*4, nsize*3, nsize, color);
    drawRectangle(x+nsize*2,y+nsize,nsize,nsize,color);
    drawRectangle(x,y+nsize*3,nsize,nsize,color);
     x-=nsize*4;
    break;
    case 6:
    drawRectangle(x,y,nsize,nsize*5,color);
    drawRectangle(x,y,nsize*3,nsize,color);
    drawRectangle(x+nsize*2,y+nsize,nsize,nsize,color);
    drawRectangle(x,y+nsize*2,nsize*3,nsize,color);
    drawRectangle(x,y+nsize*4,nsize*3,nsize,color);
     x-=nsize*4;
    break;
    case 7:
    drawRectangle(x+nsize*2,y,nsize,nsize*5,color);
    drawRectangle(x+nsize,y+nsize*4,nsize, nsize, color);
     x-=nsize*4;
    break;
    case 8:
    drawRectangle(x,y,nsize,nsize*5,color);
    drawRectangle(x+nsize*2,y,nsize,nsize*5,color);
    drawRectangle(x+nsize,y,nsize,nsize,color);
    drawRectangle(x+nsize,y+nsize*4,nsize,nsize,color);
    drawRectangle(x+nsize,y+nsize*2,nsize,nsize,color);
     x-=nsize*4;
    break;
    case 9:
    drawRectangle(x+nsize*2,y,nsize,nsize*5,color);
    drawRectangle(x,y+nsize*2,nsize*2,nsize,color);
    drawRectangle(x,y+nsize*3,nsize,nsize,color);
    drawRectangle(x,y+nsize*4,nsize*2,nsize,color);
     x-=nsize*4;
    break;
}
    } while(number);
}
int Renderer::getHeight(){
return height;
}
int Renderer::getWidth(){
return width;
}
