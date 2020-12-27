#ifndef ADVERTISEMENT_DETECTOR_H
#define ADVERTISEMENT_DETECTOR_H

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

using namespace cv;
using namespace xfeatures2d;

enum detector_t
{
	SURF,
	FAST
};

class advertisement_detecor
{
private:
	Ptr<Feature2D> detector;
	Ptr<Feature2D> extractor;
	double filter_distance_ratio;
	FlannBasedMatcher matcher;
public:
	advertisement_detecor(detector_t type);
	void set_filter_distance_ratio(double ratio);
	void detect(Mat &object, Mat &scene, std::vector<Point2f> &object_points, std::vector<Point2f> &scene_points);
};

#endif