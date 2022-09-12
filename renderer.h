#ifndef RENDERER_H
#define RENDERER_H
class Renderer{
    private:
        void* memory;
        int width;
        int height;
    public:
        Renderer(void* memory, int recWidth, int recHeight); //constructor
        void drawBackground(unsigned int color); // draws a background with a specified color

        //draws a rectangle starting at (x, y) and ending at (x+width, y+height).
        void drawRectangle(int x0, int y0, int x1, int y1, unsigned int color);

        //the same as above, BUT the values are relative to the window width or height.
        //1 is the screen size.
        void drawResponsiveRectangle(float x, float y, float recWidth, float recHeight, unsigned int color);

        //draws a number
        void drawNumber(int number, float x, float y, float nsize, unsigned int color);
        int getHeight();
        int getWidth();
};
#endif
