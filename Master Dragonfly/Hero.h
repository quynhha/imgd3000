//Thi Quynh Ha Nguyen - Master Dragonfly
// Hero.h
//

#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"
#include "Reticle.h"
#include "EventCollision.h"

class Hero : public df::Object {

 private:
  Reticle *p_reticle;
  int fire_slowdown;
  int fire_countdown;
  int move_slowdown;
  int move_countdown;
  int nuke_count;
  int life_count;
  void mouse(const df::EventMouse *p_MSE_EVENT);
  void kbd(const df::EventKeyboard *p_keyboard_event);
  void move(int dx);
  void fire(df::Vector target);
  void step();
  void jump(int dy);

  void die();

  void hit(const df::EventCollision* p_c);

 public:
  Hero();
  ~Hero();
  int eventHandler(const df::Event *p_e);
};
