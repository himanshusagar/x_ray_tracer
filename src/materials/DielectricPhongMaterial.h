//
// Created by xerious on 16/10/17.
//

#ifndef PROJECT_DIELECTRICPHONGMATERIAL_H
#define PROJECT_DIELECTRICPHONGMATERIAL_H


#include "RefractivePhongMaterial.h"

class DielectricPhongMaterial : public RefractivePhongMaterial
{

public:
    DielectricPhongMaterial(World *w);

    Color local_shade(int depth, const Ray ray, LightSource *lightSource) override;

    Color generic_shade(const Ray ray, LightSource *lightSource) override;
};


#endif //PROJECT_DIELECTRICPHONGMATERIAL_H
