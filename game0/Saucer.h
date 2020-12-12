#include "Object.h"
#include "EventCollision.h"

class Saucer : public df::Object {
private:
    void hit(const df::EventCollision* p_c);
    void moveToStart();
    void out();

public:
    Saucer();
    ~Saucer();
    int eventHandler(const df::Event* p_e);
};
