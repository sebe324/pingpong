#ifndef ENTITY_H
#define ENTITY_H
class Entity{
    protected:
        float posX;
        float posY;
        int width;
        int height;
        unsigned int color;
    public:
        Entity(float x,float y, int w, int h, unsigned int c);
        Entity();
        void setPosX(float x);
        float getPosX();
        void setPosY(float y);
        float getPosY();
        void setWidth(int x);
        int getWidth();
        void setHeight(int y);
        int getHeight();
        void setColor(unsigned int c);
        unsigned int getColor();
        bool didCollide(Entity entity);
        bool isInside(Entity entity);
        void moveVertical(float amount);
        void moveHorizontal(float amount);
};
#endif
