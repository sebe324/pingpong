#ifndef PLATFORMCOMMON_H
#define PLATFORMCOMMON_H
struct ButtonState{
 bool isDown;
 bool changed;
};
enum{
BUTTON_UP,
BUTTON_DOWN,
BUTTON_W,
BUTTON_S,

BUTTON_COUNT,
};
struct Input{
ButtonState buttons[BUTTON_COUNT];
};
#endif
