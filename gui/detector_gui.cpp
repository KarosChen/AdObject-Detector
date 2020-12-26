#include "detector_gui.h"
#define CVUI_IMPLEMENTATION
#include "cvui.h"

detector_gui::detector_gui()
{
    cvui::init(WINDOW_NAME);
    window_frame = cv::Mat(cv::Size(1000, 600), CV_8UC3);
}

void detector_gui::create()
{
    cv::Mat img;
    cvui::image(window_frame, 10, 10, img);
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
}

void detector_gui::show()
{
    cvui::imshow(WINDOW_NAME, window_frame);
    cv::waitKey(1000 / 30);
}
