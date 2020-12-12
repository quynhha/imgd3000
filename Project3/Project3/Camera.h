//
// Camera.h
//

#include "Object.h"

#define CAMERA_SPEED 0.25

class Camera : public df::Object {

 public:
  Camera();
  int eventHandler(const df::Event *p_e);
  int draw();
};

