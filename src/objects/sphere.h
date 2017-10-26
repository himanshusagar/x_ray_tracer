//sphere.h
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "setup/object.h"
#include "setup/ray.h"
#include "utils/vector3D.h"
#include "setup/color.h"

class Sphere : public Object
{
private:
	Vector3D position;
	double radius;

public:
	Sphere(const Vector3D& _pos, double _rad, Material* mat):
		Object(mat), position(_pos), radius(_rad)
	{
	}
	
	virtual bool intersect(Ray& r) const;


	Vector3D getNormal(Ray ray) const override;
};
#endif
