//
// Created by xerious on 11/10/17.
//

#ifndef ASSIGNMENT4_CYLINDER_H
#define ASSIGNMENT4_CYLINDER_H


#include <setup/object.h>

class Cylinder : public Object
{
    double radius;
    Vector3D cyOrigin;
    Vector3D cyDirection;
    Vector3D cyOppOrigin;

public:

    Cylinder(Material *mat, double radius, const Vector3D &cyOrigin, const Vector3D &cyDirection);

    bool intersect(Ray &ray) const override;

    Vector3D getNormal(Ray ray) const override;
    bool verifyT( double t , Ray ray) const;
};


#endif //ASSIGNMENT4_CYLINDER_H
