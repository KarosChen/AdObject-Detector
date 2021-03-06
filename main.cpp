#include "src/model.h"
#include <iostream>

int main()
{
	std::string detected_video_path ;
	std::string target_object_path ;
	while (true)
	{
		std::cout << "\nPlease enter detected video path !\n";
		std::cin >> detected_video_path;
		if (FILE *file = fopen(detected_video_path.c_str(), "r"))
		{
			fclose(file);
			break;
		}
	}
	while (true)
	{
		std::cout << "\nPlease enter target object path !\n";
		std::cin >> target_object_path;
		if (FILE *file = fopen(target_object_path.c_str(), "r"))
		{
			fclose(file);
			break;
		}
	}
	model model(detected_video_path, target_object_path);
	model.start();
	//model.end();
	return 0;
	//在find_Homo中 缺少一個參數8  對整體辨識的效果很重要
	/*Mat img_object_rgb = imread("C:/Users/user/Desktop/object3.png", IMREAD_ANYCOLOR);
	Mat img_object;
	img_object_rgb.copyTo(img_object);
	cvtColor(img_object, img_object, COLOR_RGB2GRAY);
	
	video_captor captor;
	captor.capture_video("C:/Users/user/Desktop/test_video.mp4");
	for (int i = 0; i < captor.get_frame_count(); i++)
	{
		Mat img_scene_rgb = captor.read_frame();
		Mat img_scene;
		img_scene_rgb.copyTo(img_scene);
		cvtColor(img_scene, img_scene, COLOR_RGB2GRAY);

		//detect good points
		advertisement_detecor detector;
		detector.set_filter_distance_ratio(0.6);
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

		imshow("video", img_scene_rgb);
		waitKey(1000 / captor.get_fps());
	}
	captor.release_video();
	*/
	/*
	Mat img_object_rgb = imread("object.png", IMREAD_ANYCOLOR);
	Mat img_scene_rgb = imread("scene.png", IMREAD_ANYCOLOR);
	Mat img_object;
	Mat img_scene;
	img_object_rgb.copyTo(img_object);
	img_scene_rgb.copyTo(img_scene);
	cvtColor(img_object, img_object, COLOR_RGB2GRAY);
	cvtColor(img_scene, img_scene, COLOR_RGB2GRAY);
	//detect good points
	advertisement_detecor detector;
	detector.set_hessian(2000);
	detector.set_filter_distance_ratio(0.6);
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
	/*
	Mat img_object = imread("object.png", IMREAD_ANYCOLOR);
	Mat img_scene = imread("scene.png", IMREAD_ANYCOLOR);


	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 400;
	Ptr<FastFeatureDetector> detector = FastFeatureDetector::create(40);
	//Ptr<SURF> detector = SURF::create(minHessian);
	std::vector<KeyPoint> keypoints_object, keypoints_scene;
	
	detector->detect(img_object, keypoints_object);
	detector->detect(img_scene, keypoints_scene);

	//-- Step 2: Calculate descriptors (feature vectors)
	Ptr<SURF> extractor = SURF::create();

	Mat descriptors_object, descriptors_scene;

	extractor->compute(img_object, keypoints_object, descriptors_object);
	extractor->compute(img_scene, keypoints_scene, descriptors_scene);

	//-- Step 3: Matching descriptor vectors using FLANN matcher
	FlannBasedMatcher matcher;
	std::vector<DMatch> matches;
	matcher.match(descriptors_object, descriptors_scene, matches);

	double max_dist = 0;
	double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i < descriptors_object.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist)
			min_dist = dist;
		if (dist > max_dist)
			max_dist = dist;
	}

	printf("-- Max dist : %f \n", max_dist);
	printf("-- Min dist : %f \n", min_dist);

	//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
	std::vector<DMatch> good_matches;

	for (int i = 0; i < descriptors_object.rows; i++)
	{
		if (matches[i].distance < max_dist * 0.6)
		{
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_matches;
	drawMatches(img_object, keypoints_object, img_scene, keypoints_scene,
				good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
				std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//-- Localize the object
	std::vector<Point2f> obj;
	std::vector<Point2f> scene;

	for (int i = 0; i < good_matches.size(); i++)
	{
		//-- Get the keypoints from the good matches
		obj.push_back(keypoints_object[good_matches[i].queryIdx].pt);
		scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
	}

	Mat H = findHomography(obj, scene, 8);

	//-- Get the corners from the image_1 ( the object to be "detected" )
	std::vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint(0, 0);
	obj_corners[1] = cvPoint(img_object.cols, 0);
	obj_corners[2] = cvPoint(img_object.cols, img_object.rows);
	obj_corners[3] = cvPoint(0, img_object.rows);
	std::vector<Point2f> scene_corners(4);

	perspectiveTransform(obj_corners, scene_corners, H);

	//-- Draw lines between the corners (the mapped object in the scene - image_2 )
	line(img_matches, scene_corners[0] + Point2f(img_object.cols, 0), scene_corners[1] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[1] + Point2f(img_object.cols, 0), scene_corners[2] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[2] + Point2f(img_object.cols, 0), scene_corners[3] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[3] + Point2f(img_object.cols, 0), scene_corners[0] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);

	//-- Show detected matches
	imshow("Good Matches & Object detection", img_matches);

	waitKey(0);
	return 0;*/
}
