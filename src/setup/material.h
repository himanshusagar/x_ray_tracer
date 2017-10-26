//matrial.h
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "color.h"
#include "ray.h"
#include "lightsource.h"
#include "camera/camera.h"
//#include "world.h"

class World;

class Material
{
protected:
	World *world;
public:
	//Data

	Color color;
    double km; //Reflection param
	double ka;//Ambient contribution
	double kd;//Diffuse constant
	double ks;//Specular constant
	double kr_reflec;//Contribution from reflection
	double kt_refrac;//Contribution from refraction
	double refractive_index;//Coefficient of refraction
	double phong_coeff;//Phong's shiny constatnt

	Material(World *w):
		world(w), color(0),
		ka(0), kd(0.0), ks(0), kr_reflec(0), kt_refrac(0),phong_coeff(0), refractive_index(0) {}


	virtual Color generic_shade(const Ray ray , LightSource* lightSource)
	{
        return Color(0.8,0.6,0.6);

	}



    //virtual Color shade(const Ray& incident, const bool isSolid) const;

};
#endif
