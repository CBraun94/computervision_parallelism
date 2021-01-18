#include <opencv4/opencv2/opencv.hpp>

#include <cmath>
#include <cstdlib>
#include <map>
#include <functional>

void colorReduce(cv::Mat& image, int div=64)
{    
    int nl = image.rows;                    // number of lines
    int nc = image.cols * image.channels(); // number of elements per line

    for (int j = 0; j < nl; j++)
    {
        // get the address of row j
        uchar* data = image.ptr<uchar>(j);

        for (int i = 0; i < nc; i++)
        {
            data[i] = data[i] / div * div + div / 2;
        }
    }
}

void example_three_one()
{
    auto a = imread("/home/christianb/Schreibtisch/studium/Share/linux/cpp/computervision_parallelism/data/5.JPG", 1);
    auto b = imread("/home/christianb/Schreibtisch/studium/Share/linux/cpp/computervision_parallelism/data/6.JPG", 1);
    
    bitwise_not(b, b);
    
    add(a,b, b);
    
    imshow("a", b);
}
