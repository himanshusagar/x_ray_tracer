#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <setup/random_gen.h>
#include <setup/ray.h>
#include "utils/vector3D.h"
#include "setup/color.h"

//#define IS_DEPTH_OF_FIELD

class Camera
{
private:
    RandomGen randomGen;
	Vector3D position;
	Vector3D target; //Look-at point
	Vector3D up;

	Vector3D line_of_sight;
	Vector3D u, v, w; //Camera basis vectors

	unsigned char *bitmap;
	int width, height;
	float fovy;// expressed in degrees: FOV-Y; angular extent of the height of the image plane
	float focalDistance; //Distance from camera center to the image plane
	float focalWidth, focalHeight;//width and height of focal plane
	float aspect;

    float radius;


public:
	Camera(const Vector3D& _pos, const Vector3D& _target, const Vector3D& _up, float fovy, int w, int h);
	~Camera();
	const Vector3D get_ray_direction(const float i, const float j) const;

    Vector3D getPosition();
    Vector3D getRandPosition();

	Ray getRayforXY(const float i , const float j);



    void drawPixel(int i, int j, Color c);
	unsigned char * getBitmap() {return bitmap; }
	int getWidth() {return width;}
	int getHeight(){return height;}

};
#endif
