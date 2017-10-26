//
// Created by xerious on 15/10/17.
//

#ifndef PROJECT_REFLECTIVEPHONGMATERIAL_H
#define PROJECT_REFLECTIVEPHONGMATERIAL_H


#include "PhongMaterial.h"

class ReflectivePhongMaterial : public PhongMaterial
{

private:
    Color local_shade( const Ray ray, LightSource *lightSource);
public:
    ReflectivePhongMaterial(World *w);

    Color generic_shade(const Ray ray, LightSource *lightSource) override;
};


#endif //PROJECT_REFLECTIVEPHONGMATERIAL_H
