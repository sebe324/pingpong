#include "renderer.h"
Renderer::Renderer(void* m, int w, int h){
memory=m;
width=w;
height=h;
}
int Renderer::clamp(int minimum, int value, int maximum){
    if(value<=minimum) return minimum;
    else if(value>=maximum) return maximum;
    else return value;
}
void Renderer::drawBackground(unsigned int color){
unsigned int* pixel = (unsigned int*)memory;
    for (int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            *pixel++=color;
        }
    }
}
void Renderer::drawRectangle(int x0, int y0, int x1, int y1, unsigned int color){
    x1=x0+x1;
    y1=y0+y1;
    x0=clamp(0,x0,width);
    y0=clamp(0,y0,height);
    x1=clamp(0,x1,width);
    y1=clamp(0,y1,height);
    for (int i=y0; i<y1; i++){
unsigned int* pixel = (unsigned int*)memory+x0+i*width; //starting pixel must be changed so it starts at rectangle x and moves as it renders another row
        for(int j=x0; j<x1; j++){
            *pixel++=color;
        }
    }
}
void Renderer::drawResponsiveRectangle(float x, float y, float sizeX, float sizeY, unsigned int color){
    sizeX=x+sizeX;
    sizeY=y+sizeY;
    x=x*height;
    y=y*height;
    sizeX=sizeX*height;
    sizeY=sizeY*height;
    int x0=clamp(0,(int)x,width);
    int y0=clamp(0,(int)y,height);
    int x1=clamp(0,(int)sizeX,width);
    int y1=clamp(0,(int)sizeY,height);
    for (int i=y0; i<y1; i++){
unsigned int* pixel = (unsigned int*)memory+x0+i*width; //starting pixel must be changed so it starts at rectangle x and moves as it renders another row
        for(int j=x0; j<x1; j++){
            *pixel++=color;
        }
    }
}
void Renderer::drawNumber(int number, float x, float y, float nsize, unsigned int color){
switch(number){
    case 0:
    drawResponsiveRectangle(x,y,nsize,nsize*5,color);
    drawResponsiveRectangle(x+nsize*2,y,nsize,nsize*5,color);
    drawResponsiveRectangle(x+nsize,y,nsize,nsize,color);
    drawResponsiveRectangle(x+nsize,y+nsize*4,nsize,nsize,color);
    break;
    case 1:
    drawResponsiveRectangle(x+nsize*2,y,nsize,nsize*5,color);
    break;
    case 2:
    drawResponsiveRectangle(x,y, nsize*3, nsize, color);
    drawResponsiveRectangle(x,y+nsize*2, nsize*3, nsize, color);
    drawResponsiveRectangle(x,y+nsize*4, nsize*3, nsize, color);
    drawResponsiveRectangle(x,y+nsize,nsize,nsize,color);
    drawResponsiveRectangle(x+nsize*2,y+nsize*3,nsize,nsize,color);

    break;
    case 3:
        drawResponsiveRectangle(x,y+nsize*2, nsize*3, nsize, color);
        drawResponsiveRectangle(x,y+nsize*4, nsize*3, nsize, color);
        drawResponsiveRectangle(x,y, nsize*3, nsize, color);
        drawResponsiveRectangle(x+nsize*2,y,nsize,nsize*4,color);

    break;
    case 4:
        drawResponsiveRectangle(x,y+nsize,nsize,nsize*3,color);
        drawResponsiveRectangle(x+nsize,y+nsize,nsize,nsize,color);
        drawResponsiveRectangle(x+nsize,y+nsize*4,nsize,nsize,color);
        drawResponsiveRectangle(x+nsize*2,y,nsize,nsize*5,color);
    break;
    case 5:
    drawResponsiveRectangle(x,y, nsize*3, nsize, color);
    drawResponsiveRectangle(x,y+nsize*2, nsize*3, nsize, color);
    drawResponsiveRectangle(x,y+nsize*4, nsize*3, nsize, color);
    drawResponsiveRectangle(x+nsize*2,y+nsize,nsize,nsize,color);
    drawResponsiveRectangle(x,y+nsize*3,nsize,nsize,color);
    break;
    case 6:
    drawResponsiveRectangle(x,y,nsize,nsize*5,color);
    drawResponsiveRectangle(x,y,nsize*3,nsize,color);
    drawResponsiveRectangle(x+nsize*2,y+nsize,nsize,nsize,color);
    drawResponsiveRectangle(x,y+nsize*2,nsize*3,nsize,color);
    drawResponsiveRectangle(x,y+nsize*4,nsize*3,nsize,color);
    break;
    case 7:
    drawResponsiveRectangle(x+nsize*2,y,nsize,nsize*5,color);
    drawResponsiveRectangle(x+nsize,y+nsize*4,nsize, nsize, color);
    break;
    case 8:
    drawResponsiveRectangle(x,y,nsize,nsize*5,color);
    drawResponsiveRectangle(x+nsize*2,y,nsize,nsize*5,color);
    drawResponsiveRectangle(x+nsize,y,nsize,nsize,color);
    drawResponsiveRectangle(x+nsize,y+nsize*4,nsize,nsize,color);
    drawResponsiveRectangle(x+nsize,y+nsize*2,nsize,nsize,color);
    break;
    case 9:
    drawResponsiveRectangle(x+nsize*2,y,nsize,nsize*5,color);
    drawResponsiveRectangle(x,y+nsize*2,nsize*2,nsize,color);
    drawResponsiveRectangle(x,y+nsize*3,nsize,nsize,color);
    drawResponsiveRectangle(x,y+nsize*4,nsize*2,nsize,color);
    break;
}
}
