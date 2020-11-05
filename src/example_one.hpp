#ifndef EXAMPLE_ONE_HPP_INCLUDED
#define EXAMPLE_ONE_HPP_INCLUDED

#include "distortion.hpp"

#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

#include <cmath>

/* https://riptutorial.com/opencv/example/6394/access-individual-pixel-values-with-cv--mat--at-t---
 * 
 *   CV_8UC1 for 8-bit 1-channel grayscale images;
 *   CV_32FC1 for 32-bit floating point 1-channel grayscale images;
 *   CV_8UC3 for 8-bit 3-channel color images; and
 *   CV_32FC3 for 32-bit floating point 3-channel color images.
 * 
 */

/*
 * Mat::at<T> access:
 * https://sodocumentation.net/de/opencv/topic/1957/pixelzugriff
 * float coordinate:
 * https://stackoverflow.com/questions/58991754/how-to-use-float-number-as-opencv-image-pixel-coordinates
 */
using MatAccess = Vec3b;

constexpr auto K1 = 0.000005;
constexpr auto K2 = 0.0;
constexpr auto P1 = 0.00000001;
constexpr auto P2 = -0.00000001;
constexpr auto P3 = 0.0;
constexpr auto P4 = 0.0;

static DistortionCoefficient 
    dcRadial(K1, K2),
    dcTangential(0.0, 0.0, P1, P2, P3, P4),
    dcFull(K1, K2, P1, P2, P3, P4);

void grid(InputOutputArray img, 
          Point center,
          int gridCount,
          int gridSize,
          const Scalar& color, 
          int thickness = 1,
          int lineType = LINE_8,
          int shift = 0)
{
    auto hg = gridCount/2;
    
    auto tl = Point(center.x-hg*gridSize, center.x-hg*gridSize);
    for(auto column = 0; column < gridCount; column++)
        for(auto row = 0; row < gridCount; row++)
            rectangle(img,
                      Point(tl.x+(gridSize*column), tl.y+(gridSize*row)),
                      Point(tl.x+(gridSize*(column+1)), tl.y+(gridSize*(row+1))),
                      color,
                      thickness,
                      lineType,
                      shift = 0);    
}

Mat doimg()
{
    auto s = 512;
    
    Mat m(Size(s, s), CV_8UC3);
    
    auto c = Point2d(s/2, s/2);
    
    auto grid_count = 10;
    auto grid_size = 25;
    
    grid(m, 
         c, 
         grid_count,
         grid_size,
         Scalar(0, 255, 0));
      
    imshow("original", m);
    
    imwrite("morig.png", m);
    
    return m;
}

void dodistortk(const Mat& s)
{
    auto size = s.size();
    auto c = Point(size.width/2, size.height/2);
    
    /* static is needed for displaying as it is a local variable */
    static Mat d(size, s.type());
    
    for(auto sw = 0; sw < size.width; sw++)
        for(auto sh = 0; sh < size.height; sh++){
            auto pd = dcRadial.transform(Point2d(sw, sh), c);
            
            if((pd.x >= 0) && (pd.x < size.width) && (pd.y >= 0) && (pd.y < size.height))
                d.at<MatAccess>(pd) = s.at<MatAccess>(Point2d(sw, sh));
        }
        
    imshow("distorted radial", d);
}

void dodistortp(const Mat& s)
{
    auto size = s.size();
    auto c = Point(size.width/2, size.height/2);
    
    /* static is needed for displaying as it is a local variable */
    static Mat d(size, s.type());
    
    for(auto sw = 0; sw < size.width; sw++)
        for(auto sh = 0; sh < size.height; sh++){
            auto pd = dcTangential.transform(Point2d(sw, sh), c);
            
            if((pd.x >= 0) && (pd.x < size.width) && (pd.y >= 0) && (pd.y < size.height))
                d.at<MatAccess>(pd) = s.at<MatAccess>(Point2d(sw, sh));
        }
        
    imshow("distorted tangential", d);
}

Mat dodistortfull(const Mat& s)
{
    auto size = s.size();
    auto c = Point(size.width/2, size.height/2);
    
    /* static is needed for displaying as it is a local variable */
    static Mat d(size, s.type());
    
    for(auto sw = 0; sw < size.width; sw++)
        for(auto sh = 0; sh < size.height; sh++){
            auto pd = dcFull.transform(Point2d(sw, sh), c);
            
            if((pd.x >= 0) && (pd.x < size.width) && (pd.y >= 0) && (pd.y < size.height))
                d.at<MatAccess>(pd) = s.at<MatAccess>(Point2d(sw, sh));
        }
        
    imshow("distorted full", d);
    
    return d;
}

Mat doundistortfull(const Mat& s)
{
    auto size = s.size();
    auto c = Point(size.width/2, size.height/2);
    
    /* static is needed for displaying as it is a local variable */
    static Mat d(size, s.type());
    
    for(auto sw = 0; sw < size.width; sw++)
        for(auto sh = 0; sh < size.height; sh++){
            auto pd = dcFull.transform(Point2d(sw, sh), c);
            
            if((pd.x >= 0) && (pd.x < size.width) && (pd.y >= 0) && (pd.y < size.height))
                d.at<MatAccess>(Point2d(sw, sh)) = s.at<MatAccess>(pd);
        }
        
    imshow("undistorted full", d);
    
    return d;
}

void example_one()
{
    auto m = doimg();
    
    dodistortk(m);
    dodistortp(m);
    auto d = dodistortfull(m);
    doundistortfull(d);
    
    auto k = waitKey(0);
}
#endif // EXAMPLE_ONE_HPP_INCLUDED
