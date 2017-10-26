//
// Created by xerious on 5/10/17.
//

#include <utils/matrix3D.h>
#include "triangle.h"

matrix3D getBetaMatrix(Vector3D origin , Vector3D main  , Vector3D sub , Vector3D left)
{
    Vector3D a = main - origin;
    Vector3D b = main - sub;
    Vector3D c = left;
    return matrix3D(a , b , c);

}

matrix3D getGammaMatrix(Vector3D origin , Vector3D main  , Vector3D sub , Vector3D left)
{
    Vector3D b = main - origin;
    Vector3D a = main - sub;
    Vector3D c = left;
    return matrix3D(a , b , c);

}
matrix3D getTMatrix(Vector3D origin , Vector3D main_a  , Vector3D main_b , Vector3D main_c)
{
    Vector3D a = main_a - main_b;
    Vector3D b = main_a - main_c;
    Vector3D c = main_a - origin;
    return matrix3D(a , b , c);

}


matrix3D getAMatrix(Vector3D main_a , Vector3D main_b  , Vector3D main_c , Vector3D left)
{
    Vector3D a = main_a - main_b;
    Vector3D b = main_a - main_c;
    Vector3D c = left;

    return matrix3D(a , b , c);

}



bool Triangle::intersect(Ray &r) const
{
    double  A = getAMatrix(position_0 , position_1 , position_2 , r.getDirection() ).getDeterminant();

    double beta = getBetaMatrix(r.getOrigin() , position_0 , position_2 , r.getDirection() ).getDeterminant();

    double  gamma = getGammaMatrix(r.getOrigin() , position_0 , position_1, r.getDirection()).getDeterminant();

    double t = getTMatrix(r.getOrigin() , position_0 , position_1 , position_2).getDeterminant();

    beta = beta/A;
    gamma = gamma/A;
    t = t/A;

    if ((gamma < 0.0) || (gamma > 1.0))
        return false;

    if ((beta < 0) || (beta > (1.0 - gamma)))
        return false;

    bool stats = r.setParameter(t , this);
    return stats;

}


Triangle::Triangle(Material *mat, const Vector3D &position_0, const Vector3D &position_1, const Vector3D &position_2)
        : Object(mat), position_0(position_0), position_1(position_1), position_2(position_2)
{
}
