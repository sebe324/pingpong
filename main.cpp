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
    Player player1(30,175,20,150,0x0984e3, 0x57, 0x53, 650);
    Player player2(840,175,20,150,0xd63031,VK_UP ,VK_DOWN, 650);
    Player players[2]={player1,player2};
    Ball ball(100,100,30,30,0xffffff,1.03);
    Renderer renderer(renderState.memory,renderState.width,renderState.height);
    Game game((renderState.width-900)/2,renderState.height-600,900,500,0x636e72, players,ball, false);
    LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    LRESULT result=0;
    switch(uMsg){
        case WM_CLOSE: case WM_DESTROY:{
            game.setPaused(true);
            PlaySound(TEXT("sounds\\pause.wav"), NULL, SND_ASYNC);
            if(MessageBox(hwnd, "Do you want to exit the game?", "Goodbye",MB_OKCANCEL | MB_ICONQUESTION)==1){
                     PlaySound(TEXT("sounds\\close.wav"), NULL, SND_ASYNC);
                      isRunning=false;
            }else{
                std::cout<<"test";
            game.setPaused(false);
            }
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
            game.setPosX((renderState.width-900)/2);
            game.setPosY(renderState.height-600);
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
    HWND window = CreateWindow(windowClass.lpszClassName, "Giga Chad Ping Pong - Made By Sebe324", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
    HDC hdc = GetDC(window);
    float deltaTime=0.16666f;
    Input input={};
    LARGE_INTEGER frameBeginTime;
    QueryPerformanceCounter(&frameBeginTime);
    float performanceFrequency;
    {
        LARGE_INTEGER perf;
        QueryPerformanceFrequency(&perf);
        performanceFrequency=(float)perf.QuadPart;
    }
    srand(time(NULL));
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
                processButton(BUTTON_MODE1, 0x31);
                processButton(BUTTON_MODE2, 0x32);
                processButton(BUTTON_PAUSE, 0x50);
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
    game.getInput(&input);
    if(!game.getPaused()){
            QueryPerformanceCounter(&frameBeginTime);
    game.setDeltaTime(deltaTime);
    //simulation
    game.simulateGame();
    //rendering
    renderer.setMemory(renderState.memory);
    renderer.setWidth(renderState.width);
    renderer.setHeight(renderState.height);
    renderer.drawBackground(0x2d3436);
    game.renderGame(&renderer);
    StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0 ,0, renderState.width, renderState.height, renderState.memory,&renderState.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
    LARGE_INTEGER frameEndTime;
    QueryPerformanceCounter(&frameEndTime);
    deltaTime=float(frameEndTime.QuadPart-frameBeginTime.QuadPart)/performanceFrequency;
    std::cout<<deltaTime<<std::endl;
    }
    }
    renderer.closeApp(0x2d3436, hdc, &renderState.bitmapInfo);
    return 0;
}
