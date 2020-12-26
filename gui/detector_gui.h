#ifndef DETECTOR_GUI
#define DETECTOR_GUI

#include <opencv2/core.hpp>
#define WINDOW_NAME "Advertisement Detector"
class detector_gui
{
public:
    detector_gui();
    void create();
    void refresh(cv::Mat &image);
    void show();
private:
    cv::Mat window_frame;

};

#endif