//sphere.cpp

#include "sphere.h"

bool Sphere::intersect(Ray& r) const
{
    Vector3D origin_minus_pos = r.getOrigin() - position;

    double a = dotProduct(r.getDirection() , r.getDirection());

    double  b = 2*dotProduct( r.getDirection() , origin_minus_pos );

    double  c = dotProduct(origin_minus_pos , origin_minus_pos) - radius*radius;

    double discriminant = b*b - 4.0*a*c;

    //now check if discr. is posivtive or zero, then only we have an intersection!
    if(discriminant >=0.0)
    {

        if(discriminant < SMALLEST_DIST)
        {
            double t;
            t = -b/(2.0*a);
            bool b = r.setParameter(t, this);
            return b;
        }
        else
        {
            //Calculate both roots
            double D = sqrt(discriminant);
            double distance_1 = (-b +D)/(2.0*a);
            double distance_2 = (-b -D)/(2.0*a);

            bool b1 = r.setParameter(distance_1, this);
            bool b2 = r.setParameter(distance_2, this);


            return b1||b2;
        }
    }
    return false;

}


Vector3D Sphere::getNormal(Ray ray) const
{
    Vector3D normal = ray.getPosition() - position;
    normal = normal/radius;
    normal.normalize();
    return normal;
}
