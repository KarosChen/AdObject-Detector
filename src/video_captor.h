#ifndef VIDEO_CAPTOR_H
#define VIDEO_CAPTOR_H

#include <stdio.h>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

class video_captor
{
private:
    VideoCapture captor;
    int frame_count;
    int fps;
public:
    void capture_video(std::string filename);
    int get_frame_count();
    int get_fps();
    bool read_frame(Mat &output);
    void release_video();
};

#endif