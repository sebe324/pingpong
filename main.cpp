#include <windows.h>
#include "renderer.h"
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
    while(isRunning){
    //get input
    MSG message;
    while (PeekMessage(&message, window, 0, 0, PM_REMOVE)){
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    //simulation
    Renderer renderer(renderState.memory,renderState.width,renderState.height);
    renderer.drawBackground(0x303030);
    renderer.drawResponsiveRectangle(0.2,0.2,0.4,0.7,0xffffff);
    /*unsigned int* pixel = (unsigned int*)renderState.memory;
    for (int i=0; i<renderState.height; i++){
        for(int j=0; j<renderState.width; j++){
            *pixel++=0x000000+j;
        }
    }*/
    //rendering
    StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0 ,0, renderState.width, renderState.height, renderState.memory,&renderState.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
    }
}
