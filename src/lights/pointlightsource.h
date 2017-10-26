#ifndef _POINTLIGHTSOURCE_H_
#define _POINTLIGHTSOURCE_H_

#include "setup/lightsource.h"

class PointLightSource : public LightSource
{

private:
	Vector3D position;

public:

	PointLightSource(World *_world, const Color &_intensity, const Vector3D &position) : LightSource(_world,
																									 _intensity),
																						 position(position) {}


    Vector3D getPosition() override {
        return position;
    }

};
#endif
