//
// Created by xerious on 11/10/17.
//

#include "Cylinder.h"


double getSquare(const Vector3D A) {
    return A.squaredlength();
    //return Vector3D(A.X() * A.X() , A.Y() * A.Y() , A.Z() * A.Z() );

}

bool Cylinder::verifyT( double t , Ray ray) const
{
    Vector3D prob = ray.getOrigin() + t*ray.getDirection();
    double alpha = dotProduct(cyDirection , prob - cyOrigin);
    double beta = dotProduct(cyDirection , prob - cyOppOrigin);
    if(alpha > 0.0 && beta < 0.0)
        return true;

    return false;


}

bool Cylinder::intersect(Ray &ray) const {

    Vector3D origin = ray.getOrigin();
    Vector3D rayDir = ray.getDirection();
    rayDir.normalize();

    Vector3D del_orig = origin - cyOrigin;

    double A, B, C;


    Vector3D tempA = (rayDir - dotProduct(rayDir, cyDirection) * cyDirection);
    A = getSquare(tempA);

    Vector3D tempB_1 = rayDir - dotProduct(rayDir, cyDirection) * cyDirection;
    Vector3D tempB_2 = del_orig - dotProduct(del_orig, cyOrigin) * cyOrigin;

    B = 2 * dotProduct(tempB_1, tempB_2);


    Vector3D tempC = (del_orig - dotProduct(del_orig, cyOrigin) * cyOrigin);
    C = getSquare(tempC);
    C = C - radius * radius;


    double discriminant = B * B - 4.0 * A * C;

    if (discriminant >= 0.0)
    {
        if (discriminant < SMALLEST_DIST)
        {
            double t;
            t = -B / (2.0 * A);
            bool b = ray.setParameter(t, this);
            return b;
        }
        else
        {
            //Calculate both roots
            double D = sqrt(discriminant);
            double distance_1 = (-B + D) / (2.0 * A);
            double distance_2 = (-B - D) / (2.0 * A);


//            bool b1 = verifyT(distance_1 , ray);
//            bool b2 = verifyT(distance_2 , ray);


            bool b1 = ray.setParameter(distance_1, this);
            bool b2 = ray.setParameter(distance_2, this);

            return b1 || b2;
        }
    }
    return false;


}

Vector3D Cylinder::getNormal(Ray ray) const {
    return Object::getNormal(ray);
}

Cylinder::Cylinder(Material *mat, double radius, const Vector3D &cyOrigin, const Vector3D &cyDirection) : Object(mat),
                                                                                                          radius(radius),
                                                                                                          cyOrigin(
                                                                                                                  cyOrigin),
                                                                                                          cyDirection(
                                                                                                                  cyDirection)
{
    cyOppOrigin = cyOrigin - Vector3D(0,10,0);

}
