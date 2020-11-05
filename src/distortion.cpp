#include "distortion.hpp"

#include "cmath"

/*
 * https://de.wikipedia.org/wiki/Entzerrung_(Fotografie)#Kompensation_mittels_Software
 * pd: distorted
 * pu: undistorted
 * pc: center of distortion
 * Kn: radial distortion coefficient
 * Pn: tangential distortion coefficient
 */
Point2d blob(Point2d pu, Point2d pc, double K1, double K2, double P1, double P2, double P3, double P4){
    Point2d pd;
    
    auto pdeltad = Point2d( pu.x-pc.x,pu.y-pc.y);
    
    double r = std::sqrt(std::pow( pdeltad.x, 2)+std::pow( pdeltad.y, 2));
    double r2 = std::pow(r, 2);
    double r4 = std::pow(r2, 2);
    
    pd.x = pc.x+(pdeltad.x)*(1+K1*r2+K2*r4)+(P2*(r2*2*std::pow(pdeltad.x,2))+2*P1*pdeltad.x*pdeltad.y)*(1+P3*r2+P4*r4);
    pd.y = pc.y+(pdeltad.y)*(1+K1*r2+K2*r4)+(P1*(r2*2*std::pow(pdeltad.y,2))+2*P2*pdeltad.x*pdeltad.y)*(1+P3*r2+P4*r4);
    
    return pd;
}

cv::Point2d DistortionCoefficient::transform ( cv::Point2d pu, cv::Point2d pc )
{
    return blob(pu, pc, K1, K2, P1, P2, P3, P4);
}
