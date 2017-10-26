//
// Created by xerious on 16/10/17.
//

#ifndef PROJECT_GLOSSYMATERIAL_H
#define PROJECT_GLOSSYMATERIAL_H


#include "PhongMaterial.h"

class GlossyMaterial : public PhongMaterial
{

public:
    GlossyMaterial(World *w);

private:
    RandomGen randomGen;

    Color local_shade( const Ray ray, LightSource *lightSource);

    Color generic_shade(const Ray ray, LightSource *lightSource) override;


};


#endif //PROJECT_GLOSSYMATERIAL_H
