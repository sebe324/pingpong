#ifndef PLATFORMCOMMON_H
#define PLATFORMCOMMON_H
struct ButtonState{
 bool isDown;
 bool changed;
};
enum{
BUTTON_P1UP,
BUTTON_P1DOWN,
BUTTON_P2UP,
BUTTON_P2DOWN,
BUTTON_MODE1,
BUTTON_MODE2,
BUTTON_PAUSE,

BUTTON_COUNT,
};
struct Input{
ButtonState buttons[BUTTON_COUNT];
};
#endif
