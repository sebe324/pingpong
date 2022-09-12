#ifndef ENTITY_H
#define ENTITY_H
class Entity{
    protected:
        int posX;
        int posY;
        int width;
        int height;
        unsigned int color;
    public:
        Entity(int x,int y, int w, int h, unsigned int c);
        Entity();
        void setPosX(int x);
        int getPosX();
        void setPosY(int y);
        int getPosY();
        void setWidth(int x);
        int getWidth();
        void setHeight(int y);
        int getHeight();
        void setColor(unsigned int c);
        unsigned int getColor();
        bool didCollide(Entity entity);
        bool isInside(Entity entity);
        void moveVertical(int amount);
        void moveHorizontal(int amount);
};
#endif
