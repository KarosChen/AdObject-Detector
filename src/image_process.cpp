#include "image_process.h"

image_process::image_process()
{
    scale_factor = 1;
}

void image_process::set_scale_factor(double scale)
{
    scale_factor = scale;
}

void image_process::resize_image(Mat &src, Mat &dst)
{
    Size new_size = src.size();
    new_size.height = new_size.height * scale_factor;
    new_size.width = new_size.width * scale_factor;
    resize(src, dst, new_size);
}

void image_process::convert_color(Mat & src, Mat &dst, int type)
{
    cvtColor(src, dst, type);
}

void image_process::draw_bouding_box(Mat &img, std::vector<Point2f> &corners)
{
    double scale = (double)(1 / scale_factor);
    line(img, corners[0] * scale, corners[1] * scale, Scalar(0, 255, 0), 4);
    line(img, corners[1] * scale, corners[2] * scale, Scalar(0, 255, 0), 4);
    line(img, corners[2] * scale, corners[3] * scale, Scalar(0, 255, 0), 4);
    line(img, corners[3] * scale, corners[0] * scale, Scalar(0, 255, 0), 4);
}