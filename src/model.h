#ifndef MODEL_H
#define MODEL_H

#include "advertisement_detector.h"
#include "transformer.h"
#include "video_captor.h"
#include "thread_pool.h"

class model
{
public:
    model();
    void detect_frame();
    void start();
    void end();
private:
    bool is_detect;
    Mat img_object_rgb;
    Mat img_object;
    video_captor captor;
    thread_pool pool;
    std::mutex captor_mutex;
};

#endif