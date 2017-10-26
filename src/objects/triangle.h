//
// Created by xerious on 5/10/17.
//

#ifndef ASSIGNMENT4_TRIANGLE_H
#define ASSIGNMENT4_TRIANGLE_H


#include "setup/object.h"

class Triangle : public Object
{
private:
    Vector3D position_0;
    Vector3D position_1;
    Vector3D position_2;

public:

    Triangle(Material *mat, const Vector3D &position_0, const Vector3D &position_1, const Vector3D &position_2);

    virtual bool intersect(Ray& r) const;

};

#endif //ASSIGNMENT4_TRIANGLE_H
