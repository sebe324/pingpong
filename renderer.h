#ifndef RENDERER_H
#define RENDERER_H
class Renderer{
    private:
        void* memory;
        int width;
        int height;
        int clamp(int minimum, int value, int maximum);
    public:
        Renderer(void* memory, int width, int height); //constructor
        void drawBackground(unsigned int color); // draws a background with a specified color

        //draws a rectangle starting at x0, y0 and ending at x0+x1 and y0+y1.
        void drawRectangle(int x0, int y0, int x1, int y1, unsigned int color);

        //the same as above, BUT the values are relative to the window width or height.
        //1 is the screen size.
        void drawResponsiveRectangle(float x, float y, float sizeX, float sizeY, unsigned int color);

};
#endif
