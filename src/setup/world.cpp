#include "world.h"

#include <iostream>
using namespace std;



bool World::firstIntersection(Ray& ray)
{
    bool isHit = false;
    //if(ray.getLevel() > 0)

	for(int i=0; i<objectList.size() ; i++)
        if(objectList[i]->intersect(ray))
        {
            isHit = true;
        }

	return isHit;
}


Color World::shade_ray(Ray& ray)
{
    Color tolColor(0);
    int lightCount =  lightSourceList.size();
    bool isHit = false;

    if(ray.getLevel() < 0)
        return Color(0);

    int normfactor = 0;

    for(int iLight = 0 ; iLight < lightCount ; iLight++)
    {
        if (firstIntersection(ray) && ray.didHit())
        {
            tolColor = tolColor + (ray.intersected())->generic_shade(ray , lightSourceList[iLight]);
            normfactor ++;
            isHit = true;
        }
    }
    if(isHit)
        return tolColor;
    else if(!isHit && ray.getLevel() < DEFAULT_RAY_DEPTH )
        return Color(0);

    return background;

}

int World::getLightsCount()
{
    return int(lightSourceList.size());

}
