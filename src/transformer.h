#ifndef PAINTER_H
#define PAINTER_H

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/types_c.h>

using namespace cv;

class transformer
{
public:
	void transform_coordinate(Mat &object, Mat &scene, std::vector<Point2f> &good_points_object, std::vector<Point2f> &good_points_scene, std::vector<Point2f> &corner_scene);
};

#endif 
