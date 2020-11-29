#include "video_captor.h"

void video_captor::capture_video(std::string filename)
{
    captor.open(filename);
    if (captor.isOpened())
    {
        Size2d frame_size = Size2d(captor.get(CAP_PROP_FRAME_WIDTH), captor.get(CAP_PROP_FRAME_HEIGHT));
        frame = Mat(frame_size, IMREAD_ANYCOLOR);
        frame_count = captor.get(CAP_PROP_FRAME_COUNT);
        fps = captor.get(CAP_PROP_FPS);
    }
    else
    {
        //error
    }
}

int video_captor::get_frame_count()
{
    return frame_count;
}

int video_captor::get_fps()
{
    return fps;
}

Mat& video_captor::read_frame()
{
    if (captor.isOpened())
    {
        captor.read(frame);
    }
    else
    {
        //error
    }
    return frame;
}

void video_captor::release_video()
{
    if (captor.isOpened())
    {
        captor.release();
    }
}

