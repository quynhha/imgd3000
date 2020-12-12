#include "ViewObject.h"
#include "Music.h"

class GameWin : public df::ViewObject {

private:
    int time_to_live;
    void step();
public:
    GameWin();
    ~GameWin();
    int eventHandler(const df::Event* p_e);
    int draw();

};

