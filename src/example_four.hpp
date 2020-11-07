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
#include <chrono> 

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
    if (iterator < accuracy) return (255*iterator)/(accuracy-1);
    else return 0;
}

void mandelbrot_loop(cv::Mat& m, int w)
{
    for(auto h=0;h<imheight;h++)
        m.at<cv::Vec3b>(cv::Point(w,h)) = cv::Vec3b(0,0,value_mandelbrot(w,h,imwidth,imheight));
}

cv::Mat example_four_one()
{
    std::cout<<"example_four_one" << std::endl << std::flush;
    
    cv::Mat m(cv::Size(imwidth, imheight), CV_8UC3);
    
    for(auto w=0;w<imwidth;w++)
        for(auto h=0;h<imheight;h++)
            m.at<cv::Vec3b>(cv::Point(w,h)) = cv::Vec3b(0,0,value_mandelbrot(w,h,imwidth,imheight));

    return m;
}

cv::Mat example_four_two()
{
    std::cout<<"example_four_two" << std::endl << std::flush;
    
    CBThreadPool p(4);
    
    cv::Mat m(cv::Size(imwidth, imheight), CV_8UC3);
    
    p.push_tasks((CBTaskFor::slice(std::bind(mandelbrot_loop, m, std::placeholders::_1), 0, imwidth-1, 1, NULL, 1, 4)));
    
    p.wait();

    return m;
}

}

void example_four(){
    std::cout<<"start of example_four" << std::endl << std::flush;

    auto start = std::chrono::high_resolution_clock::now(); 
    //auto c = exfour::example_four_one();
    auto stop = std::chrono::high_resolution_clock::now(); 
    
    auto duration = duration_cast<std::chrono::milliseconds>(stop - start); 
  
    std::cout << "Time taken singlethreaded: " << duration.count() << " milliseconds" << std::endl << std::flush; 
    
    start = std::chrono::high_resolution_clock::now(); 
    auto d = exfour::example_four_two();
    stop = std::chrono::high_resolution_clock::now();
    
    duration = duration_cast<std::chrono::milliseconds>(stop - start); 
  
    std::cout << "Time taken multithreaded: " << duration.count() << " milliseconds" << std::endl << std::flush; 
    
    cv::imshow("mandelbrot", d);
    
    //cv::imwrite("mandelbrot3.png", c);
    
    std::cout<<"end of example_three" << std::endl << std::flush;
    
    auto k = cv::waitKey();
}
#endif // EXAMPLE_FOUR_HPP_INCLUDED
