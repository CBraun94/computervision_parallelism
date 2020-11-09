#ifndef EXAMPLE_FOUR_HPP_INCLUDED
#define EXAMPLE_FOUR_HPP_INCLUDED

#include "thread/cbthreadpool.hpp"
#include "task/cbtaskanonymous.hpp"
#include "task/cbtaskfor.hpp"
#include "sync/semaphoreposix.hpp"

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

cv::Mat example_four_one()
{    
    cv::Mat m(cv::Size(imwidth, imheight), CV_8UC3);
    
    for(auto w=0;w<imwidth;w++)
        for(auto h=0;h<imheight;h++)
            m.at<cv::Vec3b>(cv::Point(w,h)) = cv::Vec3b(0,0,value_mandelbrot(w,h,imwidth,imheight));

    return m;
}

cv::Mat example_four_two()
{    
    CBThreadPool p(4);
    
    cv::Mat m(cv::Size(imwidth, imheight), CV_8UC3);
    
    p.push_tasks((CBTaskFor::slice(std::bind(mandelbrot_loop, m, std::placeholders::_1), 0, imwidth-1, 1, NULL, 1, 4)));

    return m;
}

}

void example_four(){    
    auto c = exfour::example_four_one();
    auto d = exfour::example_four_two();
    
    cv::imshow("mandelbrot", c);
    
    auto k = cv::waitKey();
}
#endif // EXAMPLE_FOUR_HPP_INCLUDED
