#include "src/advertisement_detector.h"
#include "src/transformer.h"

int main()
{
	Mat img_object = imread("object.png", IMREAD_GRAYSCALE);
	Mat img_scene = imread("scene.png", IMREAD_GRAYSCALE);
	
	//detect good points
	advertisement_detecor detector;
	detector.set_hessian(1000);
	detector.set_filter_distance_ratio(0.2);
	std::vector<Point2f> good_points_object, good_points_scene;
	detector.detect(img_object, img_scene, good_points_object, good_points_scene);

	//transform coordinate from object to scene
	transformer transformer;
	std::vector<Point2f> corner_scene(4);
	transformer.transform_coordinate(img_object, img_scene, good_points_object, good_points_scene, corner_scene);

	//draw bounding box on detected object
	Mat img_output;
	cvtColor(img_scene, img_output, COLOR_GRAY2RGB);
	line(img_output, corner_scene[0], corner_scene[1], Scalar(0, 255, 0), 4);
	line(img_output, corner_scene[1], corner_scene[2], Scalar(0, 255, 0), 4);
	line(img_output, corner_scene[2], corner_scene[3], Scalar(0, 255, 0), 4);
	line(img_output, corner_scene[3], corner_scene[0], Scalar(0, 255, 0), 4);
	imshow("Detected Image", img_output);

	waitKey(0);
}
