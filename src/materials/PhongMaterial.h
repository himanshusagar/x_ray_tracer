//
// Created by xerious on 15/10/17.
//

#ifndef PROJECT_RANDOMDIFFUSEMATERIAL_H
#define PROJECT_RANDOMDIFFUSEMATERIAL_H


#include <setup/material.h>
#include <setup/object.h>
#include <setup/world.h>

class PhongMaterial : public Material
{
public:
    PhongMaterial(World *w);

    Color generic_shade(const Ray ray, LightSource *lightSource) override;
};


#endif //PROJECT_RANDOMDIFFUSEMATERIAL_H
