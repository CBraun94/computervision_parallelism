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


static std::map<pid_t, Vec3b> tmap;

Vec3b getCol(){
    static SemaphorePosix s;
    
    Vec3b r;
    
    s.Enter();
    auto t = gettid();
    auto it = tmap.find(t);
    if(it == tmap.end()){
        tmap.insert(std::pair<pid_t, Vec3b>(t, Vec3b(rand() % 256, rand() % 256, rand() % 256)));
    }
    it = tmap.find(t);
    r = (*it).second;
    s.Leave();
    
    return r;
}

void randcol(cv::Mat& m, int i)
{
    Vec3b p = getCol();
    m.at<Vec3b>(i) = p;
}

Mat example_three_two(int minChunkSize = 0)
{
    CBThreadPool p(2);
    
    cv::Mat m(Size(imsize, imsize), CV_8UC3);
    
    p.push_tasks(CBTaskFor::slice(std::bind(randcol, m, std::placeholders::_1), 0, m.cols*m.rows, 1, NULL, minChunkSize));

    p.wait();

    return m;
}

}

void example_three(){
    auto a = exthree::example_three_two(0);
    
    cv::imshow("randcol_one", a);
    
    auto k = waitKey();
    
    auto b = exthree::example_three_two(exthree::imsize);
    
    cv::imshow("randcol_two", b);
    
     k = waitKey();
}

#endif // EXAMPLE_THREE_HPP_INCLUDED
