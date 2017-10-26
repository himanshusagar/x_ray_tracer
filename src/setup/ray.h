//ray.h
#ifndef _RAY_H_
#define _RAY_H_

#include <float.h>
#include "utils/vector3D.h"


#define DEFAULT_RAY_DEPTH 3

class Object;

const float SMALLEST_DIST = 1e-5; //Constant used to dismiss intersections very close to previous
class Ray
{
private:
    Vector3D origin;
	Vector3D direction;
	float t; //Distance travelled along the Ray
	bool hit; //has the ray hit something?
	const Object *object;//The object that has been hit
	int level;//Number of times the ray has been traced recursively
	float refractive_index;
	Vector3D normal; //Normal of the hit object



public:  
	Ray(const Vector3D& o, const Vector3D& d):
    		origin(o), direction(d), t(FLT_MAX), hit(false)
	{
        level = DEFAULT_RAY_DEPTH;
		direction.normalize();
        refractive_index = 1.0;

	}

    Ray(const Vector3D& o, const Vector3D& d, int _level):
            origin(o), direction(d), t(FLT_MAX), hit(false)
    {
        direction.normalize();
        level = _level;
        refractive_index = 1.0;
    }



    Vector3D getOrigin() const  {return origin;}
	Vector3D getDirection() const  {return direction;}
	Vector3D getPosition() const {return origin + t*direction;}
	Vector3D getNormal() const {return normal;}
	float getParameter() const {return t;}
	bool setParameter(const float par, const Object *obj);
	bool didHit() const {return hit;}
	const Object* intersected() const {return object;}
	int getLevel() const {return level;}
    int setLevel(int _level) { level = _level; }


	void setUpdatedDirection(Vector3D d) { d.normalize() ; direction = d;}
    void moveOriginAlongDirection() { origin.normalize() ; origin = origin + direction * 1e-4; }


};
#endif
