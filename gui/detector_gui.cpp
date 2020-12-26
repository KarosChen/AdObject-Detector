#include "detector_gui.h"
#define CVUI_IMPLEMENTATION
#include "cvui.h"

detector_gui::detector_gui()
{
    cvui::init(WINDOW_NAME);
    window_frame = cv::Mat(cv::Size(800, 600), CV_8UC3);
}

void detector_gui::create()
{
    cv::Mat img;
    cvui::image(window_frame, 10, 10, img);
}

void detector_gui::refresh(cv::Mat &image)
{
    window_frame = cv::Scalar(49, 52, 49);
    cvui::image(window_frame, 10, 10, image);
}

void detector_gui::show()
{
    cvui::imshow(WINDOW_NAME, window_frame);
    cv::waitKey(1000 / 30);
}
