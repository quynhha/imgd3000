#include "Object.h"
#include "EventCollision.h"

class EnemyBullet : public df::Object {

private:
    void out();
    void hit(const df::EventCollision* p_collision_event);

public:
    EnemyBullet(df::Vector ene_pos);
    int eventHandler(const df::Event* p_e);
};
