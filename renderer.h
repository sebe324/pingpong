class Renderer{
    private:
        void* memory;
        int width;
        int height;
        int clamp(int minimum, int value, int maximum);
    public:
        Renderer(void* memory, int width, int height); //constructor
        void drawBackground(unsigned int color); // draws a background with a specified color
        //draws a rectangle starting at x0, y0 and ending at x1,y1.
        //for example if you want a 100 by 100 pixels rectangle starting at 50, 90 then it would look like this drawRectangle(50, 90, 150, 190, color)
        void drawRectangle(int x0, int y0, int x1, int y1, unsigned int color);
        //the same as above, BUT the values are relative to the window width or height. If window width is greater than window height then values will be relative to the height and vice versa.
        //1 is the screen size.
        void drawResponsiveRectangle(float x, float y, float sizeX, float sizeY, unsigned int color);

};
