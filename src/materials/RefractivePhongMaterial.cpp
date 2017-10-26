//
// Created by xerious on 15/10/17.
//

#include "RefractivePhongMaterial.h"

RefractivePhongMaterial::RefractivePhongMaterial(World *w) : PhongMaterial(w) {
    refractive_index = 1.2;

    ka = 0.1;// % ambient reflection coefficient
    kd = 0.4;// % diffuse reflection coefficient
    ks = 0.5; //% specular reflection coefficient

    km = 0.4;


    color = Color(0.7, 0.01 , 0.9);//Color(0.1 * randomGen.getNumber() , 0.7* randomGen.getNumber() , 0.4 * randomGen.getNumber());
    refractive_index = 0.90;
    phong_coeff = 1.0; //% spectral exponent

}



Color RefractivePhongMaterial::local_shade(int depth , const Ray ray, LightSource *lightSource)
{
    Color phongRefrac =  PhongMaterial::generic_shade(ray, lightSource);

    Vector3D normal = ray.intersected()->getNormal(ray);
    Vector3D outward_normal;
    double refractive_index_Ratio , reflect_probability;

    if (depth < 0)
        return phongRefrac;

    std::pair<bool , Vector3D> reflectStats =  reflectRay(ray , normal);
    Vector3D reflectDirection  = reflectStats.second;

    //Main Code Starts
    if (dotProduct(ray.getDirection(), normal) > 0)
    {
        outward_normal = -normal;
        refractive_index_Ratio = refractive_index;

    }
    else
    {
        outward_normal = normal;
        refractive_index_Ratio = 1.0 / refractive_index;
    }

    std::pair<bool, Vector3D> refractStats = refractRay(ray.getDirection(), outward_normal, refractive_index_Ratio);
    Vector3D refractDirection = refractStats.second;
    Ray scatteredRay(Vector3D(0) , Vector3D(0));


    if (refractStats.first == true)
    {
        scatteredRay.setUpdatedDirection(refractDirection);
    }
    else
    {
//        reflect_probability = 1.0;
        scatteredRay.setUpdatedDirection(reflectDirection);

    }

    world->firstIntersection(scatteredRay);

    if (scatteredRay.didHit())
    {
        phongRefrac = phongRefrac + local_shade( depth - 1 , scatteredRay , lightSource);// , ray , normal)/5;

    }

    return phongRefrac;


}

Color RefractivePhongMaterial::generic_shade(const Ray ray, LightSource *lightSource)
{
    int depth=3;
    return local_shade(depth , ray , lightSource);
}



std::pair<bool, Vector3D> RefractivePhongMaterial::refractRay(Vector3D direction, Vector3D normal, double ratio_ref_index)
{
    Vector3D uv = direction;
    uv.normalize();

    double dt = dotProduct(uv, normal);
    double discriminant = 1.0 - ratio_ref_index * ratio_ref_index * (1.0 - dt * dt);

    if (discriminant > 0)
    {
        Vector3D refracted = ratio_ref_index * (direction - normal * dt) - normal * sqrt(discriminant);
        refracted.normalize();
        return std::make_pair(true, refracted);
    }

    return std::make_pair(false, Vector3D(0));

}

std::pair<bool, Vector3D > RefractivePhongMaterial::reflectRay(Ray ray, Vector3D normal)
{
    Vector3D refNormal = (ray.intersected())->getNormal(ray);


    Vector3D reflectionDirection = ray.getDirection() - refNormal * 2 * (dotProduct(ray.getDirection(), refNormal));

    reflectionDirection.normalize();
    return std::make_pair(true, reflectionDirection);
}