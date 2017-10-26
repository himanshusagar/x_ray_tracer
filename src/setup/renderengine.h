#ifndef _RENDERENGINE_H_
#define _RENDERENGINE_H_

#pragma once
#include "world.h"
#include "camera/camera.h"
#include "random_gen.h"

class RenderEngine
{
private:
	World *world;
	Camera *camera;
	const Color trace(const float i, const float j);

public:
	RenderEngine(World *_world, Camera *_camera):
		world(_world), camera(_camera) {}
	bool renderLoop();

    RandomGen xRandomGen;
    RandomGen yRandomGen;

};
#endif
