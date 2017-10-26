#include "camera.h"

Camera::Camera(const Vector3D& _pos, const Vector3D& _target, const Vector3D& _up, float _fovy, int _width, int _height) : 
position(_pos), target(_target), up(_up), fovy(_fovy), width(_width), height(_height)
{
	up.normalize();

	line_of_sight = target - position;

	//Calculate the camera basis vectors
	//Camera looks down the -w axis
	w = -line_of_sight;
	w.normalize();
	u = crossProduct(up, w);
	u.normalize();
	v = crossProduct(w, u);
	v.normalize();
	bitmap  = new unsigned char[width * height * 3]; //RGB
	for (size_t i = 0; i < 3*width*height; ++i) {
		bitmap[i] = 0;
	}
	focalHeight = 1.0; //Let's keep this fixed to 1.0

	aspect = float(width)/float(height);

    focalWidth = focalHeight * aspect; //Height * Aspect ratio

    focalDistance = focalHeight/(2.0 * tan(fovy * M_PI/(180.0 * 2.0))); //More the fovy, close is focal plane

	radius = 0.01;
}

Camera::~Camera()
{
	delete []bitmap;
}

//Get direction of viewing ray from pixel coordinates (i, j)
const Vector3D Camera::get_ray_direction(const float i, const float j) const
{
	Vector3D dir(0.0, 0.0, 0.0);
	dir += -w * focalDistance;

    float xw = aspect*(i - width/2.0 + 0.5)/width;
	float yw = (j - height/2.0 + 0.5)/height;

    dir += u * xw;
	dir += v * yw;

	dir.normalize();
	return dir;
}

void Camera::drawPixel(int i, int j, Color c)
{
	int index = (i + j*width)*3;
	bitmap[index + 0] = 255 * c.r ;
	bitmap[index + 1] = 255 * c.g;
	bitmap[index + 2] = 255 * c.b;
}


Vector3D Camera::getPosition()
{

#ifdef IS_DEPTH_OF_FIELD
    double root_r = sqrt(radius*randomGen.getNumber());
    double theta = 2 * M_PI * randomGen.getNumber();

    Vector3D randPos = position;
    randPos.X( randPos.X() + root_r * cos(theta));
    randPos.Z(randPos.Z() + root_r * sin(theta));
    //NO need to update Y because it is where up vector points

    return randPos;
#else
    return position;
#endif


}

Ray Camera::getRayforXY(const float i, const float j)
{

	Vector3D currPosition = getPosition();

	up.normalize();

	line_of_sight = target - currPosition;

	//Calculate the camera basis vectors
	//Camera looks down the -w axis
	w = -line_of_sight;
	w.normalize();
	u = crossProduct(up, w);
	u.normalize();
	v = crossProduct(w, u);
	v.normalize();


	Vector3D dir(0.0, 0.0, 0.0);
	dir += -w * focalDistance;

	float xw = aspect*(i - width/2.0 + 0.5)/width;
	float yw = (j - height/2.0 + 0.5)/height;


	dir += u * xw;
	dir += v * yw;

	dir.normalize();

    return Ray( currPosition , dir);


}

Vector3D Camera::getRandPosition() {

}
