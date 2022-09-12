#include <windows.h>
#include <iostream>
#include "renderer.h"
#include "platformCommon.h"
#include "game.h"
#include <ctime>
#include "player.h"
bool isRunning = true;
struct RenderState {
void *memory;
int width;
int height;
BITMAPINFO bitmapInfo;
};
RenderState renderState;
LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    LRESULT result=0;
    switch(uMsg){
//
        case WM_CLOSE: case WM_DESTROY:{
            isRunning=false;
        }
        break;
    //
        case WM_SIZE:
            {
            RECT rect;
            GetClientRect(hwnd, &rect);
            renderState.width = rect.right-rect.left;
            renderState.height = rect.bottom - rect.top;
            int bufferSize = renderState.width*renderState.height*sizeof(unsigned int);
            if(renderState.memory) VirtualFree(renderState.memory, 0, MEM_RELEASE);

            renderState.memory = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            renderState.bitmapInfo.bmiHeader.biSize=sizeof(renderState.bitmapInfo.bmiHeader);
            renderState.bitmapInfo.bmiHeader.biWidth=renderState.width;
            renderState.bitmapInfo.bmiHeader.biHeight=renderState.height;
            renderState.bitmapInfo.bmiHeader.biPlanes=1;
            renderState.bitmapInfo.bmiHeader.biBitCount=32;
            renderState.bitmapInfo.bmiHeader.biCompression=BI_RGB;
        }break;
    default:  result = DefWindowProc(hwnd, uMsg, wParam, lParam); break;
    }
return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    WNDCLASS windowClass = {};
    windowClass.style= CS_HREDRAW | CS_VREDRAW;
    windowClass.lpszClassName = "Ping Pong Game";
    windowClass.lpfnWndProc = WindowCallback;

    RegisterClass(&windowClass);
    HWND window = CreateWindow(windowClass.lpszClassName, "Ping Pong Game", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
    HDC hdc = GetDC(window);

    Input input={};
    float deltaTime=0.016666f;
    LARGE_INTEGER frameBeginTime;
    QueryPerformanceCounter(&frameBeginTime);
    float performanceFrequency;
    {
        LARGE_INTEGER perf;
        QueryPerformanceFrequency(&perf);
        performanceFrequency=(float)perf.QuadPart;
    }
    srand(time(NULL));
    Player player1(30,175,20,150,0x0984e3, 0x57, 0x53);
    Player player2(840,175,20,150,0xd63031,VK_UP ,VK_DOWN);
    Player players[2]={player1,player2};
    Ball ball(100,100,30,30,0xffffff,0.8);
    Game game((renderState.width-900)/2,renderState.height-600,900,500,0x636e72, players,ball);
    while(isRunning){
    //get input
    MSG message;

    for(int i=0; i<BUTTON_COUNT; i++){
        input.buttons[i].changed=false;
    }
    while (PeekMessage(&message, window, 0, 0, PM_REMOVE)){
            switch(message.message){
            case WM_KEYUP:
            case WM_KEYDOWN:{
                unsigned int vkCode =(unsigned int)message.wParam;
                bool isDown = ((message.lParam & (1<<31))==0);
#define processButton(b, vk)\
    if(vkCode==vk){\
        input.buttons[b].isDown=isDown;\
        input.buttons[b].changed= isDown != input.buttons[b].isDown;\
        }
                const int p1up=player1.getBtnUp();
                const int p1down=player1.getBtnDown();
                processButton(BUTTON_P1UP, player1.getBtnUp());
                processButton(BUTTON_P1DOWN, player1.getBtnDown());
                processButton(BUTTON_P2UP, player2.getBtnUp());
                processButton(BUTTON_P2DOWN, player2.getBtnDown());
                }break;
        default:
                TranslateMessage(&message);
        DispatchMessage(&message);
            break;
            }
    }
    //simulation
    game.simulateGame(&input,deltaTime);
    //rendering
    Renderer renderer(renderState.memory,renderState.width,renderState.height);
    renderer.drawBackground(0x2d3436);
    game.renderGame(&renderer);
    StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0 ,0, renderState.width, renderState.height, renderState.memory,&renderState.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
    LARGE_INTEGER frameEndTime;
    QueryPerformanceCounter(&frameEndTime);
    deltaTime=float(frameEndTime.QuadPart-frameBeginTime.QuadPart)/performanceFrequency;
    frameBeginTime=frameEndTime;
    }
    return 0;
}
