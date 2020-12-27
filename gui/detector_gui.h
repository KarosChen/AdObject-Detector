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
    int get_mode_state();
    bool get_start_state();
    int get_interval();
private:
    cv::Mat window_frame;
    char *mode_label;
    int mode_state;
    char *start_label;
    bool start_state;
    int interval;
};

#endif