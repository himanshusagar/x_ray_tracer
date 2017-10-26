//
// Created by xerious on 15/10/17.
//

#include "ReflectivePhongMaterial.h"

ReflectivePhongMaterial::ReflectivePhongMaterial(World *w) : PhongMaterial(w)
{
    km = 0.3;
}


Color ReflectivePhongMaterial::local_shade(const Ray ray, LightSource *lightSource)
{
    Color phongReflectance = PhongMaterial::generic_shade(ray, lightSource);

    Vector3D point = ray.getPosition();
    Vector3D refNormal = (ray.intersected())->getNormal(ray);
    Vector3D reflectionDirection = ray.getDirection() - refNormal * 2 * (dotProduct(ray.getDirection(), refNormal));

    Ray reflectionRay(point + reflectionDirection * 1e-4, reflectionDirection , ray.getLevel() - 1);

    return phongReflectance + km * world->shade_ray(reflectionRay);

}

Color ReflectivePhongMaterial::generic_shade(const Ray ray, LightSource *lightSource) {

    return local_shade(ray , *(&lightSource));

}
