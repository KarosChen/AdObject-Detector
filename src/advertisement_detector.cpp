#include "advertisement_detector.h"
#include <ctime>
advertisement_detecor::advertisement_detecor()
{
	filter_distance_ratio = 0.2;
	//detector = SURF::create();
	detector = FastFeatureDetector::create();
	extractor = SURF::create();
}

void advertisement_detecor::set_filter_distance_ratio(double ratio)
{
	filter_distance_ratio = ratio;
}

void advertisement_detecor::detect(Mat &object, Mat &scene, std::vector<Point2f> &good_points_object, std::vector<Point2f> &good_points_scene)
{
	clock_t a, b;
	//detect keypoints
	std::vector<KeyPoint> keypoints_object, keypoints_scene;
	detector->detect(object, keypoints_object);
	detector->detect(scene, keypoints_scene);

	//extract descriptor
	Mat descriptor_object, descriptor_scene;
	extractor->compute(object, keypoints_object, descriptor_object);
	extractor->compute(scene, keypoints_scene, descriptor_scene);

	a = clock();

	//match descriptor
	std::vector<DMatch> matches;
	matcher.match(descriptor_object, descriptor_scene, matches);

	b = clock();
	printf("%3.8f       ", double(b - a) / CLOCKS_PER_SEC);

	//find max and min distance
	double max_dis = 0, min_dis = 100;
	for (int i = 0; i < descriptor_object.rows; i++)
	{
		double dis = matches[i].distance;
		if (dis < min_dis)
		{
			min_dis = dis;
		}
		if (dis > max_dis)
		{
			max_dis = dis;
		}
	}

	std::vector<DMatch> good_matches;
	//filter similar descriptor
	if (max_dis > 0)
	{
		for (int i = 0; i < descriptor_object.rows; i++)
		{
			if (matches[i].distance < (max_dis * filter_distance_ratio))
			{
				good_matches.push_back(matches[i]);
			}
		}
	}
	else
	{
		good_matches = matches;
	}

	for (int i = 0; i < good_matches.size(); i++)
	{
		int object_index = good_matches[i].queryIdx;
		int train_index = good_matches[i].trainIdx;
		good_points_object.push_back(keypoints_object[object_index].pt);
		good_points_scene.push_back(keypoints_scene[train_index].pt);
	}
}
