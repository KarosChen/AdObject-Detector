#ifndef ADVERTISEMENT_DETECTOR_H
#define ADVERTISEMENT_DETECTOR_H

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

using namespace cv;
using namespace xfeatures2d;

class advertisement_detecor
{
private:
	int hessian;
	double filter_distance_ratio;
	Ptr<SURF> detector;
	Ptr<SURF> extractor;
	FlannBasedMatcher matcher;

public:
	advertisement_detecor();
	void set_hessian(int threshold);
	void set_filter_distance_ratio(double ratio);
	void detect(Mat &object, Mat &scene, std::vector<Point2f> &object_points, std::vector<Point2f> &scene_points);
};

#endif