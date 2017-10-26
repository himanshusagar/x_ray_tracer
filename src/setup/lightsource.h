#ifndef _LIGHTSOURCE_H_
#define _LIGHTSOURCE_H_

#include "color.h"
#include "utils/vector3D.h"

class World;
class LightSource
{	
protected:
	World *world;
	Color intensity;
public:
	LightSource(World *_world, const Color _intensity):
		world(_world), intensity(_intensity)   {}
	virtual Vector3D getPosition() { return  Vector3D(0); }
	Color getIntensity() const {return intensity; }

};
#endif
