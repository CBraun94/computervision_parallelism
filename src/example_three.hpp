#ifndef EXAMPLE_THREE_HPP_INCLUDED
#define EXAMPLE_THREE_HPP_INCLUDED

#include "thread/cbthreadpool.hpp"
#include "task/cbtaskanonymous.hpp"
#include "task/cbtaskfor.hpp"
#include "sync/semaphoreposix.hpp"

#include <sys/types.h> /* linux specific */
#include <unistd.h> /* linux specific */
#include <sys/syscall.h> /* linux specific */

#include <opencv4/opencv2/opencv.hpp>

#include <cmath>
#include <cstdlib>
#include <map>
#include <functional>

namespace exthree{
    constexpr auto imsize = 512;


static std::map<pid_t, cv::Vec3b> tmap;

cv::Vec3b getCol(){
    static SemaphorePosix s;
    
    cv::Vec3b r;
    
    s.Enter();
    auto t = gettid();
    auto it = tmap.find(t);
    if(it == tmap.end()){
        tmap.insert(std::pair<pid_t, cv::Vec3b>(t, cv::Vec3b(rand() % 256, rand() % 256, rand() % 256)));
    }
    it = tmap.find(t);
    r = (*it).second;
    s.Leave();
    
    return r;
}

void randcol(cv::Mat& m, int i)
{
    cv::Vec3b p = getCol();
    m.at<cv::Vec3b>(i) = p;
}

cv::Mat example_three_two(int threadCount = 8, int minChunkSize = 0)
{
    std::cout<<"example_three_two" << std::endl << std::flush;
    
    CBThreadPool p(threadCount);
    
    cv::Mat m(cv::Size(imsize, imsize), CV_8UC3);
    
    p.push_tasks(CBTaskFor::slice(std::bind(randcol, m, std::placeholders::_1), 0, m.cols*m.rows, 1, NULL, minChunkSize));

    //sleep(1);
    std::cout<<"example_three_two: wait start" << std::endl << std::flush;
    p.wait();
    std::cout<<"example_three_two: wait end" << std::endl << std::flush;

    return m;
}

}

void example_three(){
    std::cout<<"start of example_three" << std::endl << std::flush;
    
    auto a = exthree::example_three_two(32, 5);
    
    std::cout<<"start of example_three 50" << std::endl << std::flush;
    
    cv::imshow("randcol_one", a);
    
    auto k = cv::waitKey();
    
    auto b = exthree::example_three_two(4, exthree::imsize);
    
    cv::imshow("randcol_two", b);
    
    std::cout<<"end of example_three" << std::endl << std::flush;
    
     k = cv::waitKey();
}

#endif // EXAMPLE_THREE_HPP_INCLUDED
