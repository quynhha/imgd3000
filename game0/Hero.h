/*
Hero.h
*/
#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Reticle.h"
#include "EventCollision.h"


class Hero : public df::Object {
private:
    Reticle* p_reticle;
    int move_slowdown;
    int move_countdown;
    int fire_slowdown;
    int fire_countdown;
    int nuke_count;
    int life_count;
    void kbd(const df::EventKeyboard* p_keyboard_event);
    void move(int dy);
    void step();
    void mouse(const df::EventMouse* p_mouse_event);
    void fire(df::Vector target);
    void nuke();

public:
    Hero();
    ~Hero();
    int eventHandler(const df::Event* p_e);
    void hit(const df::EventCollision* p_c);
    void die();
};
