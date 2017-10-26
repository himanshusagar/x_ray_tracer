//
// Created by xerious on 16/10/17.
//

#include <algorithm>
#include "GlossyMaterial.h"

#define SQUARE_LENGTH 2


Vector3D changeSmallestComp(const Vector3D t)
{
    Vector3D retVal = t;

    std::vector<double> vec;
    vec.push_back( fabs(t.X()) ) ; vec.push_back( fabs(t.Y()) ); vec.push_back( fabs(t.Z()) );

    auto minIt = std::min_element(vec.begin() , vec.end());
    int index = minIt - vec.begin();


    if(index == 0)
        retVal.X(1);
    else if(index == 1)
        retVal.Y(1);
    else if(index == 2)
        retVal.Z(1);
    else
        exit(1);

    return retVal;


}
Color GlossyMaterial::local_shade(const Ray ray, LightSource *lightSource)
{
    Color phongReflectance = PhongMaterial::generic_shade(ray, lightSource);

    Vector3D point = ray.getPosition();
    Vector3D refNormal = (ray.intersected())->getNormal(ray);
    Vector3D reflectionDirection = ray.getDirection() - refNormal * 2 * (dotProduct(ray.getDirection(), refNormal));
    reflectionDirection.normalize();

//    Ray reflectionRay(point, reflectionDirection , ray.getLevel() - 1);
  //  reflectionRay.moveOriginAlongDirection();

    Vector3D as = changeSmallestComp( Vector3D(1/sqrt(2) , (-1)/sqrt(2) , 0) );

    Vector3D w = reflectionDirection;
    w.normalize();

    Vector3D t = w;
    t = changeSmallestComp(t);
    t.normalize();

    Vector3D u = crossProduct(t, w);
    u.normalize();

    Vector3D v = crossProduct(w, u);
    v.normalize();


    float eeta1= randomGen.getNumber();
    float eeta2  =randomGen.getNumber();

    double coord_u = -SQUARE_LENGTH/2 + eeta1 * SQUARE_LENGTH;
    double coord_v = -SQUARE_LENGTH/2 + eeta2 * SQUARE_LENGTH;

    Vector3D reflectionDashDirection = reflectionDirection + coord_u*u + coord_v*v;
    reflectionDashDirection.normalize();

    Ray reflectionRay(point  , reflectionDirection , ray.getLevel() - 1);
    reflectionRay.moveOriginAlongDirection();

    return phongReflectance + km * world->shade_ray(reflectionRay);

}

Color GlossyMaterial::generic_shade(const Ray ray, LightSource *lightSource)
{
    return local_shade(ray , lightSource);
}

GlossyMaterial::GlossyMaterial(World *w) : PhongMaterial(w) {
    km = 0.3;
    ka = 0.5;

    color = Color(0 , 1 , 1);
}
