#include "detector_gui.h"
#define CVUI_IMPLEMENTATION
#include "cvui.h"

detector_gui::detector_gui()
{
    mode = "SURF";
    start_label = "Start";
    start_state = false;
    initial_interval = 10;
    cvui::init(WINDOW_NAME);
    window_frame = cv::Mat(cv::Size(1000, 600), CV_8UC3);
}

void detector_gui::create()
{
    cv::Mat img = cv::Mat(cv::Size(800, 590), CV_8UC3);
    cvui::image(window_frame, 5, 5, img);
    cvui::text(window_frame, 850, 5, mode);
    cvui::button(window_frame, 850, 105, 100, 60, "SURF");
    cvui::button(window_frame, 850, 205, 100, 60, "FAST");
    cvui::trackbar(window_frame, 810, 305, 180, &initial_interval, (int)5, (int)30, (int)5, "%.0Lf", cvui::TRACKBAR_DISCRETE | cvui::TRACKBAR_HIDE_STEP_SCALE, (int)5);
    cvui::button(window_frame, 850, 405, 100, 60, start_label);
}

void detector_gui::refresh(cv::Mat &image)
{
    cv::Size new_size = image.size();
    new_size.width = 800;
    new_size.height = 590;
    cv::Mat tar;
    cv::resize(image, tar, new_size);
    window_frame = cv::Scalar(49, 52, 49);
    cvui::image(window_frame, 5, 5, tar);
    if (cvui::button(window_frame, 850, 105, 100, 60, "SURF"))
    {
        mode = "SURF";
    }
    if (cvui::button(window_frame, 850, 205, 100, 60, "FAST"))
    {
        mode = "FAST";
    }
    if (!start_state)
    {
        if (cvui::button(window_frame, 850, 405, 100, 60, start_label))
        {
            if (!start_state)
            {
                start_label = "Stop";
                start_state = true;
            }
        }
    }   
    cvui::text(window_frame, 850, 5, mode);
    cvui::trackbar(window_frame, 810, 305, 180, &initial_interval, (int)5, (int)30, (int)5, "%.0Lf", cvui::TRACKBAR_DISCRETE | cvui::TRACKBAR_HIDE_STEP_SCALE, (int)5);
}

void detector_gui::show()
{
    cvui::imshow(WINDOW_NAME, window_frame);
    cv::waitKey(1000 / 30);
}

bool detector_gui::get_start_state()
{
    return start_state;
}
