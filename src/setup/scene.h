//
// Created by xerious on 15/10/17.
//

#ifndef PROJECT_SCENE_H
#define PROJECT_SCENE_H


#include "camera/camera.h"
#include "renderengine.h"

class Scene
{
private:
    Camera *mCamera;
    World *mWorld;
    RenderEngine *mRenderEngine;

public:


    Scene(int screen_width, int screen_height);
    bool isRenderLoopRunning();

    unsigned char * getBitmap() {return mCamera->getBitmap(); }

};


#endif //PROJECT_SCENE_H
