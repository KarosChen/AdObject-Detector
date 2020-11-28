#include "video_captor.h"

void video_captor::capture_video(std::string filename)
{
    VideoCapture captor(filename);
    Size2d frame_size = Size2d(captor.get(CAP_PROP_FRAME_WIDTH), captor.get(CAP_PROP_FRAME_HEIGHT));
    Mat frame(frame_size, IMREAD_ANYCOLOR);
    int count = captor.get(CAP_PROP_FRAME_COUNT);
    int fps = captor.get(CAP_PROP_FPS);
    printf("%d, %d", count, fps);
    for (int i = 0; i < 60; i++)
    {
        captor.read(frame);
        imshow("video", frame);
        waitKey(1000/fps);
    }

    captor.release();
}

