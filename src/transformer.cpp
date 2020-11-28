#include "transformer.h"
//transform object corner coordinate to scene coordinate
void transformer::transform_coordinate(Mat &object, Mat &scene, std::vector<Point2f> &good_points_object, std::vector<Point2f> &good_points_scene, std::vector<Point2f> &corner_scene)
{
	Mat T = findHomography(good_points_object, good_points_scene);
	
	std::vector<Point2f> corner_object(4);
	
	corner_object[0] = cvPoint(0, 0);
	corner_object[1] = cvPoint(object.cols, 0);
	corner_object[2] = cvPoint(object.cols, object.rows);
	corner_object[3] = cvPoint(0, object.rows);

	perspectiveTransform(corner_object, corner_scene, T);
}