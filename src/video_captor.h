#ifndef VIDEO_CAPTOR_H
#define VIDEO_CAPTOR_H

#include <stdio.h>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

class video_captor
{
public:
    void capture_video(std::string filename);
};

#endif