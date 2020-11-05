#ifndef DISTORTION_HPP_INCLUDED
#define DISTORTION_HPP_INCLUDED

#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

Point2d blob(Point2d pu, Point2d pc, double K1, double K2 = 0.0, double P1 = 0.0, double P2 = 0.0, double P3 = 0.0, double P4 = 0.0);

class DistortionCoefficient{
public:
    DistortionCoefficient(double K1 = 0.0, double K2 = 0.0, 
                          double P1 = 0.0, double P2 = 0.0, double P3 = 0.0, double P4 = 0.0):
                          K1(K1), K2(K2), 
                          P1(P1), P2(P2), P3(P3), P4(P4) {}; 
                          
    double K1, K2;
    double P1, P2, P3, P4;
    
    Point2d transform(Point2d pu, Point2d pc);
};

#endif // DISTORTION_HPP_INCLUDED
