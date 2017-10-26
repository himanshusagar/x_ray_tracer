#include <cstdlib>
#include <random>
#include "renderengine.h"



const Color RenderEngine::trace(const float i, const float j)
{

#ifdef IS_DEPTH_OF_FIELD
    Ray ray = camera->getRayforXY(i , j);
#else
	Vector3D ray_dir = camera->get_ray_direction(i, j);
	Ray ray(camera->getPosition(), ray_dir);
#endif
    return world->shade_ray(ray);

}


#define JITTER_VAL 2.0f

bool RenderEngine::renderLoop()
{
	static int i = 0;

	for(int j = 0; j < (camera->getHeight()) ; j++)
	{
		Color tolColor = trace(i , j);

		for (int p = 0; p < (JITTER_VAL ) ; ++p)
		{
			for (int q = 0; q < (JITTER_VAL); ++q)
			{
                float eeta = xRandomGen.getNumber();
                float eeta2 = yRandomGen.getNumber();

				Color pqColor = trace( i + (p + eeta)/JITTER_VAL  , j + (q + eeta2)/JITTER_VAL );
				pqColor.clamp();
				tolColor = tolColor +  pqColor;
			}

		}



        tolColor  = tolColor / (JITTER_VAL*JITTER_VAL);
        tolColor.clamp();

		camera->drawPixel(i, j, tolColor);

	}

	if(++i == camera->getWidth())
	{
		i = 0;
		return true;
	}
	return false;
}
