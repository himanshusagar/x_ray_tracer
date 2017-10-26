//
// Created by xerious on 15/10/17.
//

#include <utils/vector3D.h>
#include <objects/sphere.h>

#include <materials/ReflectivePhongMaterial.h>
#include <materials/RefractivePhongMaterial.h>
#include <materials/DielectricPhongMaterial.h>
#include <materials/GlossyMaterial.h>
#include "lights/arealightsource.h"
#include "scene.h"

#define X_DIFF_FACTOR 50

Scene::Scene(int screen_width, int screen_height)
{

    mWorld = new World();

    Vector3D primary_lightPosition(0 , 150 , 0 );
    Color primary_lightColor(0.2);


    //Initialize raytracer objects
   Vector3D camera_position(0, 10, 20);
    Vector3D top(-5 ,60 , -1);
    //camera_position = top;

    Vector3D camera_target(0, 0, 0); //Looking down -Z axis
    Vector3D camera_up(0, 1, 0);
    float camera_fovy =  45;
    mCamera = new Camera(camera_position, camera_target, camera_up, camera_fovy, screen_width, screen_height);
    //Create a mWorld

    mWorld->setAmbient(Color(1));

    mWorld->setBackground(Color(0));

    //mWorld->setBackground(Color(0.1, 0.3, 0.6));
    mWorld->setBackground(Color(1, 1, 1));

    ReflectivePhongMaterial *matl = new ReflectivePhongMaterial(mWorld);//new RandomDiffuseMaterial(mWorld);
    matl->color = Color( 0, 1 , 0 );

    ReflectivePhongMaterial *triMat = new ReflectivePhongMaterial(mWorld);

    auto *gMat = new GlossyMaterial(mWorld);

    RefractivePhongMaterial *refractivePhongMaterial = new RefractivePhongMaterial(mWorld);

    DielectricPhongMaterial *dielectricPhongMaterial = new DielectricPhongMaterial(mWorld);

    ReflectivePhongMaterial *plateMaterial = new ReflectivePhongMaterial(mWorld);


    plateMaterial->ka = 0.5;// % ambient reflection coefficient
    plateMaterial->kd = 0.3;// % diffuse reflection coefficient
    plateMaterial->ks = 0.2; //% specular reflection coefficient
    plateMaterial->km = 0.8;
    plateMaterial->color = Color(1, 0 , 0);
    plateMaterial->phong_coeff = 10.0; //% spectral exponent
    //scr = 0.5;



    triMat->ka = 0.2;// % ambient reflection coefficient
    triMat->kd = 0.4;// % diffuse reflection coefficient
    triMat->ks = 0.4; //% specular reflection coefficient
    triMat->km = 0.5;
    triMat->color = Color(99.0/255.0, 184.0/255.0 , 255.0/255.0);
    triMat->phong_coeff = 100.0; //% spectral exponent
    //scr = 0.5;




    Object *sphere = new Sphere(Vector3D(2, 0, -10), 4, dielectricPhongMaterial);
    mWorld->addObject(sphere);

    Object *sphere2 = new Sphere(Vector3D(-8, 0, -10), 2, plateMaterial );
    mWorld->addObject(sphere2);

    Object *sphere3 = new Sphere(Vector3D(-9.5, 0, 3), 3, gMat );
    mWorld->addObject(sphere3);

    Object *sphere7 = new Sphere(Vector3D( -5 , 0, 3), 1, triMat );
    mWorld->addObject(sphere7);

    Object *sphere4 = new Sphere(Vector3D(9, 0, 3), 1, refractivePhongMaterial );
    mWorld->addObject(sphere4);



    //vetices need to be IN COUNTER_CLOCKWISE Direction

    //(1,3), (-2,-2) and (3,-1):
//    Object *triangle = new Triangle( triMat ,  Vector3D(-5 , -5 , -3 )  , Vector3D(0,-5 , 5) , Vector3D( -2.5 , 2.5, 4 ) );
//    mWorld->addObject(triangle);



    //Material *simpleMat = new Material(mWorld);

    Object *plate = new Sphere(Vector3D(0, -103, -1), 100, matl);
    mWorld->addObject(plate);


    Object *backgrnd = new Sphere(Vector3D(0, 0, -200), 100, triMat);
    mWorld->addObject(backgrnd);

//    Object *cylinder = new Cylinder( boxMat  , 1.0 , Vector3D( 0  ,0 , 0) , Vector3D(1 ,0 , 0) );
//    mWorld->addObject(cylinder);

    int N = 2;
    for(int i = 0 ; i < N ; i ++)
    {
        double Movement  =  -((N/2)* X_DIFF_FACTOR) + ( (i+1)* X_DIFF_FACTOR);

        Vector3D iLightPost(primary_lightPosition.X()  + Movement ,
                            primary_lightPosition.Y() ,
                            primary_lightPosition.Z() + Movement);

        LightSource *iLight = new AreaLightSource(mWorld, primary_lightColor , iLightPost);
        mWorld->addLight(iLight);
    }

    mRenderEngine = new RenderEngine(mWorld, mCamera);

}

bool Scene::isRenderLoopRunning() {
    return mRenderEngine->renderLoop();
}


