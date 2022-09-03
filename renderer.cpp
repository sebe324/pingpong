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
    if(width>height){
    x=x*height;
    y=y*height;
    sizeX=sizeX*height;
    sizeY=sizeY*height;
    }else{
    x=x*width;
    y=y*width;
    sizeX=sizeX*width;
    sizeY=sizeY*width;
    }
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
