#ifndef EXAMPLE_FOUR_HPP_INCLUDED
#define EXAMPLE_FOUR_HPP_INCLUDED

#include "../cbparallel/thread/cbthreadpool.hpp"
#include "../cbparallel/task/cbtaskanonymous.hpp"
#include "../cbparallel/task/cbtaskfor.hpp"
#include "../cbparallel/sync/semaphoreposix.hpp"

#include "log.hpp"

#include <opencv4/opencv2/opencv.hpp>

#include <cmath>
#include <cstdlib>
#include <map>
#include <functional>

#include <complex>

namespace exfour{
    constexpr auto imsize = 1024*2;
    constexpr auto imwidth = imsize;
    constexpr auto imheight = imsize;
    
    constexpr auto accuracy = 256;


int value_mandelbrot(int x, int y, int width, int height)  {
    std::complex<float> p((float)x/width-1.5, (float)y/height-0.5);
    std::complex<float> z(0, 0);
    unsigned int iterator = 0;
    
    while (abs (z) < 2 && iterator <= accuracy)
    {
        z = z * z + p;
        iterator++;
    }
    if
        (iterator < accuracy) return (255*iterator)/(accuracy-1);
    else
        return 0;
}

void mandelbrot_loop(cv::Mat& m, int w)
{
    for(auto h=0;h<imheight;h++)
        m.at<cv::Vec3b>(cv::Point(w,h)) = cv::Vec3b(0,0,value_mandelbrot(w,h,imwidth,imheight));
}

void example_four_one(cv::Mat &m)
{        
    for(auto w=0;w<imwidth;w++)
        for(auto h=0;h<imheight;h++)
            m.at<cv::Vec3b>(cv::Point(w,h)) = cv::Vec3b(0,0,value_mandelbrot(w,h,imwidth,imheight));
}

void example_four_two(cv::Mat &m)
{    
    CBThreadPool p(4);
    
    p.push_tasks((CBTaskFor::slice(std::bind(mandelbrot_loop, m, std::placeholders::_1), 0, imwidth-1, 1, NULL, 1, 4)));
}

void example_four_three(cv::Mat &m)
{    
    CBThreadPool p(4);
    
    p.push_tasks((CBTaskFor::slice(std::bind(mandelbrot_loop, m, std::placeholders::_1), 0, imwidth-1, 1, NULL, 100, 4)));
}

}

void example_four(){    
    using namespace exfour;
    cv::Mat c(cv::Size(imwidth, imheight), CV_8UC3),d(cv::Size(imwidth, imheight), CV_8UC3),e(cv::Size(imwidth, imheight), CV_8UC3);
    
    cb::timetaken("mandelbrot parallel, minchunksize line*51", std::bind(exfour::example_four_three, e));
    cb::timetaken("mandelbrot parallel, minchunksize line", std::bind(exfour::example_four_two, d));
    cb::timetaken("mandelbrot sequential", std::bind(exfour::example_four_one, c));  
    
    cv::imshow("mandelbrot", c);
    
    auto k = cv::waitKey();
}
#endif // EXAMPLE_FOUR_HPP_INCLUDED
