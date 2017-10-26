//
// Created by xerious on 16/10/17.
//


#ifndef PROJECT_AREALIGHTSOURCE_H
#define PROJECT_AREALIGHTSOURCE_H

#include "setup/random_gen.h"
#include "pointlightsource.h"

class AreaLightSource : public LightSource
{
private:
    RandomGen randomGen;
    Vector3D center;
    Vector3D side_a;
    Vector3D side_b;


public:
    AreaLightSource(World *_world, const Color &_intensity, const Vector3D &center, const Vector3D &side_a,
                    const Vector3D &side_b) : LightSource(_world, _intensity), center(center), side_a(side_a),
                                              side_b(side_b) {

    }

#define INC_FACTOR 10

    AreaLightSource(World *_world, const Color &_intensity, const Vector3D &center) : LightSource(_world, _intensity),
                                                                                      center(center)
    {

        //we would want a to be on the right side ; just a convention
        // and b needs to lie above c ; Note that Y remains constant here ; we can pass param to decide who remains constant


        side_a = Vector3D(center.X() + INC_FACTOR , center.Y() , center.Z());
        side_b = Vector3D(center.X() , center.Y() , center.Z() + INC_FACTOR);


    }


public:

    Vector3D getPosition()  override
    {

        float eeta1= randomGen.getNumber();
        float eeta2  =randomGen.getNumber();

        Vector3D randPosition = center + eeta1 * side_a + eeta2*side_b;
       //randPosition.normalize();
        return randPosition;
    }



};


#endif //PROJECT_AREALIGHTSOURCE_H
