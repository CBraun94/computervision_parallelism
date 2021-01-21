#ifndef EXAMPLE_THREE_HPP_INCLUDED
#define EXAMPLE_THREE_HPP_INCLUDED

#include "cbparallel/thread/cbthreadpool.hpp"
#include "cbparallel/task/cbtaskanonymous.hpp"
#include "cbparallel/task/cbtaskfor.hpp"
#include "cbparallel/sync/semaphoreposix.hpp"

#include <opencv4/opencv2/opencv.hpp>

#include <cmath>
#include <cstdlib>
#include <map>
#include <functional>

namespace exthree{
    constexpr auto imsize = 512;
    constexpr auto imwidth = imsize;
    constexpr auto imheight = imsize;

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
    CBThreadPool p(threadCount);
    
    cv::Mat m(cv::Size(imsize, imsize), CV_8UC3);
    
    p.push_tasks(CBTaskFor::slice(std::bind(randcol, m, std::placeholders::_1), 0, m.cols*m.rows, 1, NULL, minChunkSize));

    return m;
}

}

void example_three(){
    auto a = exthree::example_three_two(32, 25);
    auto b = exthree::example_three_two(4, exthree::imsize);
    
    cv::imshow("randcol_one", a);
    cv::imshow("randcol_two", b); 
    
    auto k = cv::waitKey();
}

#endif // EXAMPLE_THREE_HPP_INCLUDED
