#ifndef DISTORTION_HPP_INCLUDED
#define DISTORTION_HPP_INCLUDED

#include <opencv4/opencv2/opencv.hpp>

cv::Point2d blob(cv::Point2d pu, cv::Point2d pc, double K1, double K2 = 0.0, double P1 = 0.0, double P2 = 0.0, double P3 = 0.0, double P4 = 0.0);

class DistortionCoefficient{
public:
    DistortionCoefficient(double K1 = 0.0, double K2 = 0.0, 
                          double P1 = 0.0, double P2 = 0.0, double P3 = 0.0, double P4 = 0.0):
                          K1(K1), K2(K2), 
                          P1(P1), P2(P2), P3(P3), P4(P4) {}; 
                          
    double K1, K2;
    double P1, P2, P3, P4;
    
    cv::Point2d transform(cv::Point2d pu, cv::Point2d pc);
};

#endif // DISTORTION_HPP_INCLUDED
