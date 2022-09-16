#include "renderer.h"
#include "utils.h"
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <cmath>
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
void Renderer::drawBackground2(int x, int y, unsigned int recWidth, unsigned int recHeight, unsigned int color){
    x=Utils::clamp(0, x,width);
    y=Utils::clamp(0, y, height);
    for(int i=0; i<y; i++){
        unsigned int* pixel=(unsigned int*)memory+i*width;
        for(int j=0; j<width; j++){
            *pixel++=color;
        }
    }
    for(int i=y; i<recHeight+y; i++){
        unsigned int* pixel=(unsigned int*)memory+i*width;
        for(int j=0; j<x; j++){
            *pixel++=color;
        }
    }
    for(int i=y; i<recHeight+y; i++){
            unsigned int* pixel=(unsigned int*)memory+i*width+recWidth+x;
        for(int j=recWidth+x; j<width; j++){
            *pixel++=color;
        }
    }
    for(int i=y+recHeight; i<height; i++){
            unsigned int* pixel=(unsigned int*)memory+i*width;
        for(int j=0; j<width; j++){
            *pixel++=color;
        }
    }
}
void Renderer::drawBorder(int x, int y, unsigned int recWidth, unsigned int recHeight, unsigned int thickness, unsigned int color){
    x=Utils::clamp(0, x,width);
    y=Utils::clamp(0, y, height);
    int x1=Utils::clamp(0,recWidth+x,width);
    int y1=Utils::clamp(0,recHeight+y,height);
    for(int i=y; i<y+thickness; i++){
        unsigned int* pixel=(unsigned int*)memory+i*width+x;
        for(int j=x; j<x1; j++){
            *pixel++=color;
        }
    }
    for(int i=y; i<y1; i++){
        unsigned int* pixel=(unsigned int*)memory+i*width+x;
        for(int j=x; j<x+thickness; j++){
            *pixel++=color;
        }
    }
    for(int i=y1-thickness; i<y1; i++){
            unsigned int* pixel=(unsigned int*)memory+i*width+x;
        for(int j=x; j<x1; j++){
            *pixel++=color;
        }
    }
    for(int i=y; i<y1; i++){
        unsigned int* pixel=(unsigned int*)memory+i*width+x1-thickness;
        for(int j=x1-thickness; j<x1; j++){
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
void Renderer::drawText(std::string text, float x, float y, float tsize, unsigned int color){
for(int i=0; i<text.length(); i++){
    switch(text[i]){
    case '.':
            {
            bool letter[5][5]={
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,1,0,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
        case '0':
            {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
        case '1':
            {
            bool letter[5][5]={
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
        case '2':
            {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,0,0,1,0},
            {0,1,1,1,0},
            {0,1,0,0,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
        case '3':
            {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,0,0,1,0},
            {0,1,1,1,0},
            {0,0,0,1,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
        case '4':
            {
            bool letter[5][5]={
            {0,0,1,1,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            {0,0,0,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
        case '5':
            {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,1,0,0,0},
            {0,1,1,1,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
        case '6':
            {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,1,0,0,0},
            {0,1,1,1,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
        case '7':
            {
            bool letter[5][5]={
            {0,0,1,1,0},
            {0,0,0,1,0},
            {0,0,1,1,0},
            {0,0,0,1,0},
            {0,0,0,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
        case '8':
            {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
        case '9':
            {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            {0,0,0,1,0},
            {0,0,0,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
        case 'a':
            {
            bool letter[5][5]={
            {0,0,1,0,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
          case 'b':
              {
            bool letter[5][5]={
            {0,1,1,0,0},
            {0,1,0,1,0},
            {0,1,1,0,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
          case 'c':
              {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,1,0,0,0},
            {0,1,0,0,0},
            {0,1,0,0,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
          case 'd':
              {
            bool letter[5][5]={
            {0,1,1,0,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,1,0,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
          case 'e':
              {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,1,0,0,0},
            {0,1,1,1,0},
            {0,1,0,0,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
          case 'f':
              {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,1,0,0,0},
            {0,1,1,1,0},
            {0,1,0,0,0},
            {0,1,0,0,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
          case 'g':
              {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,1,0,0,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
          case 'h':
              {
            bool letter[5][5]={
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
          case 'i':
              {
            bool letter[5][5]={
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
          case 'j':
              {
            bool letter[5][5]={
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,1,1,0,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
          case 'k':
              {
            bool letter[5][5]={
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,1,0,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
          case 'l':
              {
            bool letter[5][5]={
            {0,1,0,0,0},
            {0,1,0,0,0},
            {0,1,0,0,0},
            {0,1,0,0,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
          case 'm':
              {
            bool letter[5][5]={
            {0,0,0,0,0},
            {0,0,0,0,0},
            {1,1,1,1,1},
            {1,0,1,0,1},
            {1,0,1,0,1},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
         case 'n':
             {
            bool letter[5][5]={
            {1,0,0,1,0},
            {1,1,0,1,0},
            {1,0,1,1,0},
            {1,0,0,1,0},
            {1,0,0,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
         case 'o':
             {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
             }
        break;
         case 'p':
             {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            {0,1,0,0,0},
            {0,1,0,0,0},
            };
            drawLetter(letter,x,y,tsize,color);
             }
        break;
         case 'q':
             {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            {0,0,0,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
        break;
              case 'r':
                  {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,1,0,1,0},
            {0,1,1,0,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
            break;
                    case 's':
                        {
            bool letter[5][5]={
            {0,0,1,1,0},
            {0,1,0,0,0},
            {0,1,1,1,0},
            {0,0,0,1,0},
            {0,1,1,0,0},
            };
            drawLetter(letter,x,y,tsize,color);
             }
            break;
                    case 't':
                        {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            };
            drawLetter(letter,x,y,tsize,color);
             }
            break;
                    case 'u':
                        {
            bool letter[5][5]={
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
             }
            break;
                case 'v':
                    {
            bool letter[5][5]={
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,0,1,0,0},
            };
            drawLetter(letter,x,y,tsize,color);
             }
            break;
                    case 'w':
                        {
            bool letter[5][5]={
            {1,0,1,0,1},
            {1,0,1,0,1},
            {1,0,1,0,1},
            {1,0,1,0,1},
            {0,1,0,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
            }
            break;
                    case 'x':
                        {
            bool letter[5][5]={
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,0,1,0,0},
            {0,1,0,1,0},
            {0,1,0,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
             }
            break;
                   case 'y':
                       {
            bool letter[5][5]={
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            };
            drawLetter(letter,x,y,tsize,color);
             }
            break;
                   case 'z':
                       {
            bool letter[5][5]={
            {0,1,1,1,0},
            {0,0,0,1,0},
            {0,0,1,0,0},
            {0,1,0,0,0},
            {0,1,1,1,0},
            };
            drawLetter(letter,x,y,tsize,color);
             }
            break;
    }
x+=6*tsize;

}
}
void Renderer::drawLetter(bool letter[5][5], float x, float y, float lsize, unsigned int color){
for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
        if(letter[i][j])drawRectangle(x+lsize*j,y+lsize*abs(i-5),lsize,lsize,color);
    }
}
}
void Renderer::closeApp(unsigned int color, HDC hdc, BITMAPINFO* bitmapinfo){
    drawBackground(0xdfe6e9);
    for (int i=0; i<height/2; i+=std::ceil(height/200)){
            for(int k=1; k<=std::ceil(height/200); k++){
                unsigned int* pixel = (unsigned int*)memory+(i+k)*width;
        for(int j=0; j<width; j++){
            *pixel++=color;
        }
            }
            for(int k=1; k<=std::ceil(height/200); k++){
            unsigned int *pixel2=(unsigned int*)memory+(height-i-k)*width;
              std::cout<<height-i-k<<std::endl;
             for(int j=0; j<width; j++){
            *pixel2--=color;
        }
            }
        Sleep(7);
        StretchDIBits(hdc, 0, 0, width, height, 0 ,0, width, height, memory,bitmapinfo, DIB_RGB_COLORS, SRCCOPY);
    }
}
void Renderer::setMemory(void* m){
memory=m;
}
void Renderer::setWidth(int w){
width=w;
}
void Renderer::setHeight(int h){
height=h;
}
