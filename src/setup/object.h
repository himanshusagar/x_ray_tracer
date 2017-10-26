//object.h
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ray.h"
#include "utils/vector3D.h"
#include "color.h"
#include "material.h"
#include "lights/pointlightsource.h"
#include "material.h"


class Object
{

public:
    Material *material;

    Object(Material *mat): material(mat) {}
	virtual bool intersect(Ray& ray) const = 0;

    virtual Color generic_shade(const Ray &ray , LightSource* lightSource) const
    {
        return material->generic_shade(ray , lightSource);
    }



    virtual Vector3D getNormal(Ray ray) const
    {
        return Vector3D(0);
    }


};

#endif
