//
// Created by xerious on 10/10/17.
//

#ifndef ASSIGNMENT4_MATRIX3D_H
#define ASSIGNMENT4_MATRIX3D_H


#include <utils/vector3D.h>

class matrix3D
{
    Vector3D col_p;
    Vector3D col_q;
    Vector3D col_r;


public:
    matrix3D(const Vector3D &col_p, const Vector3D &col_q, const Vector3D &col_r);

    double getDeterminant();

};


#endif //ASSIGNMENT4_MATRIX3D_H
