//
// Created by xerious on 15/10/17.
//

#include "PhongMaterial.h"

PhongMaterial::PhongMaterial(World *w) : Material(w)
{
    ka = 0.3;// % ambient reflection coefficient
    kd = 0.4;// % diffuse reflection coefficient
    ks = 0.5; //% specular reflection coefficient

    km = 0.8;


    color = Color(1.0 , 1.0 , 1.0);//Color(0.1 * randomGen.getNumber() , 0.7* randomGen.getNumber() , 0.4 * randomGen.getNumber());
    refractive_index = 1.5;

    phong_coeff = 1.0; //% spectral exponent
    //scr = 0.5;
}

Color PhongMaterial::generic_shade(const Ray ray, LightSource *lightSource)
{
    Vector3D normal = ray.intersected()->getNormal(ray);

    Vector3D lightVector = lightSource->getPosition() - ray.getPosition();
    Vector3D viewVector = -( ray.getDirection());
    viewVector.normalize();
    lightVector.normalize();


    Color one = (color * ka);///world->getLightsCount();

    Vector3D point = ray.getPosition();
    Vector3D shdowDirection =  lightVector; // OR  =  lightSource->getPosition() - point;
    shdowDirection.normalize();

    Ray shadow_ray(point + shdowDirection * 1e-4, shdowDirection);
    world->firstIntersection(shadow_ray);
    Color c= one;

    if (!shadow_ray.didHit())
    {

        Vector3D h =  lightVector + viewVector;
        h.normalize();

        Color two = lightSource->getIntensity() * kd * fmax(0, dotProduct(normal, lightVector));

       // Color three = lightSource->getIntensity() * ks * pow(fmax(0, dotProduct(normal, h)), phong_coeff);

        Color three = lightSource->getIntensity() * ks * pow( dotProduct(normal , h) , phong_coeff);
        c = c + two + three;// + shadow(shadow_ray, lightSource, ray, normal) / 5;
    }


    return c;

}
