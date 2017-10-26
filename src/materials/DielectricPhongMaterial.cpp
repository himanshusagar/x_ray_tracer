//
// Created by xerious on 16/10/17.
//

#include "DielectricPhongMaterial.h"

DielectricPhongMaterial::DielectricPhongMaterial(World *w) : RefractivePhongMaterial(w) {
    refractive_index = 0.99;
    ka =  0.2;


}

double schilck_Approx( double cosine , double ref_index)
{
    double r_0 = (1- ref_index) / (1+ref_index);
    r_0 = r_0 * r_0;
    return r_0 + (1.0-r_0) * pow( (1 - cosine) , 5);

}


Color DielectricPhongMaterial::generic_shade(const Ray ray, LightSource *lightSource)
{
    int depth=3;
    return local_shade(depth , ray , lightSource);
}

Color DielectricPhongMaterial::local_shade(int depth, const Ray ray, LightSource *lightSource)
{

    Color diColor =  PhongMaterial::generic_shade(ray, lightSource);

    Vector3D normal = ray.intersected()->getNormal(ray);
    normal.normalize();

    Vector3D rayDirection = ray.getDirection();
    rayDirection.normalize();

    Vector3D outward_normal;
    double refractive_index_Ratio;


    std::pair<bool , Vector3D> reflectStats =  reflectRay(ray , normal);
    Vector3D reflectDirection  = reflectStats.second;
    std::pair<bool, Vector3D> refractStats;

    double cosine;

    Color k_rgb(1);
    Color log_a_rgb(0.001 , 0.01 , 0.1);

    //Main Code Starts
    if (dotProduct( rayDirection , normal) < 0)
    {
        //Enter Dielectric
        outward_normal = normal;
        refractive_index_Ratio = refractive_index;

        refractStats = refractRay( rayDirection, outward_normal, refractive_index_Ratio);

        cosine =  - (dotProduct( rayDirection , normal ) ) / rayDirection.length();
        k_rgb = Color(1);

    }
    else
    {

        outward_normal = -(normal);
        refractive_index_Ratio = 1.0 / refractive_index;

        k_rgb.r = exp(-log_a_rgb.r * ray.getParameter());
        k_rgb.g = exp(-log_a_rgb.g * ray.getParameter());
        k_rgb.b = exp(-log_a_rgb.b * ray.getParameter());

        refractStats = refractRay(rayDirection, outward_normal, refractive_index_Ratio);

        if (refractStats.first)
        {
            cosine = dotProduct(refractStats.second, normal);
        }
        else
        {
            Ray reflectRay(ray.getPosition(), reflectDirection  , ray.getLevel() - 1);
            diColor = diColor + k_rgb * world->shade_ray(reflectRay);
            return diColor;
        }
    }

    double schilck_R = schilck_Approx(cosine , refractive_index);

    Ray reflectComp = Ray(ray.getPosition() , reflectDirection , ray.getLevel() - 1);
    diColor = diColor + schilck_R * world->shade_ray(reflectComp);


//    if(refractStats.first)
//    {
        Ray refractComp = Ray(ray.getPosition() , refractStats.second , ray.getLevel() - 1);
        diColor = diColor + (1.0 - schilck_R)*world->shade_ray(refractComp );

   // }

    return diColor*k_rgb;

}

