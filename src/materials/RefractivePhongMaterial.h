//
// Created by xerious on 15/10/17.
//

#ifndef PROJECT_REFRACTIVEPHONGMATERIAL_H
#define PROJECT_REFRACTIVEPHONGMATERIAL_H


#include "ReflectivePhongMaterial.h"

class RefractivePhongMaterial : public PhongMaterial
{
public:
    RefractivePhongMaterial(World *w);


    virtual Color local_shade(int depth , const Ray ray, LightSource *lightSource);
    Color generic_shade(const Ray ray, LightSource *lightSource) override;


    std::pair<bool, Vector3D > reflectRay(Ray ray, Vector3D normal);
    std::pair<bool, Vector3D> refractRay(Vector3D direction, Vector3D normal, double ratio_ref_index);


};


#endif //PROJECT_REFRACTIVEPHONGMATERIAL_H
