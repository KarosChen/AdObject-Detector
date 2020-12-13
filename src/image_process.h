#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include <opencv2/imgproc.hpp>

using namespace cv;

class image_process
{
public:
    image_process();
    void set_scale_factor(double scale);
    void resize_image(Mat &src, Mat &dst);
    void convert_color(Mat &src, Mat &dst, int type);
    void draw_bouding_box(Mat &img, std::vector<Point2f> &corners);
private:
    double scale_factor;
};

#endif