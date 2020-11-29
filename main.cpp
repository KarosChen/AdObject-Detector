#include "src/advertisement_detector.h"
#include "src/transformer.h"
#include "src/video_captor.h"

int main()
{
	/*
	Mat img_object_rgb = imread("object.png", IMREAD_ANYCOLOR);
	Mat img_scene_rgb = imread("scene.png", IMREAD_ANYCOLOR);
	Mat img_object;
	Mat img_scene;
	img_object_rgb.copyTo(img_object);
	img_scene_rgb.copyTo(img_scene);
	
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
	line(img_scene_rgb, corner_scene[0], corner_scene[1], Scalar(0, 255, 0), 4);
	line(img_scene_rgb, corner_scene[1], corner_scene[2], Scalar(0, 255, 0), 4);
	line(img_scene_rgb, corner_scene[2], corner_scene[3], Scalar(0, 255, 0), 4);
	line(img_scene_rgb, corner_scene[3], corner_scene[0], Scalar(0, 255, 0), 4);
	imshow("Detected Image", img_scene_rgb);

	waitKey(0);*/
	video_captor captor;
	captor.capture_video("C:/Users/user/Desktop/test_video.mp4");
	Mat frame;
	printf("%d", captor.get_fps());
	for (int i = 0; i < 60; i++)
	{
		frame = captor.read_frame();
        imshow("video", frame);
        waitKey(1000 / captor.get_fps());
	}
	captor.release_video();
}
