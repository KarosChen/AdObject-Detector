#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "image_process.h"
#include "advertisement_detector.h"
#include "transformer.h"
#include "video_captor.h"
#include "thread_pool.h"
#include "../gui/detector_gui.h"

class model
{
public:
    model(std::string video, std::string target);
    void detect_frame();
    void play_frame();
    void start();
    void end();

private:
    bool is_start;
    detector_t d_type;
    int interval;
    Mat img_object_rgb;
    Mat img_object;
    image_process processor;
    video_captor captor;
    thread_pool pool;
    std::mutex captor_mutex;
    std::vector<Mat> output_imgs;
    std::mutex output_imgs_mutex;
    //clock_t a, b;
};

#endif