#include "model.h"

model::model()
{
    pool.create_threads(5);
    is_detect = true;
    interval = 10; 
    img_object_rgb = imread("C:/Users/user/Desktop/object3.png", IMREAD_ANYCOLOR);
    img_object_rgb.copyTo(img_object);
    cvtColor(img_object, img_object, COLOR_RGB2GRAY);
    captor.capture_video("C:/Users/user/Desktop/test_video.mp4");
}

void model::detect_frame()
{
    if (is_detect)
    {
        std::vector<Mat> img_scene_rgbs;
        {
            std::unique_lock<std::mutex> lock(captor_mutex);
            for (int i = 0; i < interval; i++)
            {
                Mat img_scene_rgb;
                if(captor.read_frame(img_scene_rgb))
                {
                    img_scene_rgbs.emplace_back(img_scene_rgb);  
                }
            }
        }
        Mat img_scene;
        img_scene_rgbs.front().copyTo(img_scene);
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
        for (int i = 0; i < interval; i++)
        {
            line(img_scene_rgbs[i], corner_scene[0], corner_scene[1], Scalar(0, 255, 0), 4);
            line(img_scene_rgbs[i], corner_scene[1], corner_scene[2], Scalar(0, 255, 0), 4);
            line(img_scene_rgbs[i], corner_scene[2], corner_scene[3], Scalar(0, 255, 0), 4);
            line(img_scene_rgbs[i], corner_scene[3], corner_scene[0], Scalar(0, 255, 0), 4);
            output_imgs.emplace_back(img_scene_rgbs[i]);
        }
    }
}

//play frame in output images vector
void model::play_frame()
{
    int frame_num = 0;
    
    while (true)
    {
        if (output_imgs.size() > frame_num)
        {
            imshow("video", output_imgs[frame_num]);
            frame_num ++;
            waitKey(1000 / captor.get_fps());
        }
    }
}

//start model
void model::start()
{
    std::function<void()> play_frame = std::bind(&model::play_frame, this);
    pool.enqueue_task(play_frame);

    for (int i = 0; i < captor.get_frame_count(); i = i + interval)
    {
        std::function<void()> exe_fun = std::bind(&model::detect_frame, this);
        pool.enqueue_task(exe_fun);
    }
    /*Test Time code
    clock_t a, b;
    a = clock();
    for (int i = 0; i < 30; i++)
    {
        detect_frame();
    }
    for (int i = 0; i < 30; i++)
    {
        std::function<void()> exe_fun = std::bind(&model::detect_frame, this);
        pool.enqueue_task(exe_fun);
    }
    while (temp.size() < 30)
    {}
    b = clock();
    printf("%3.8f       ", double(b - a) / CLOCKS_PER_SEC);*/
}

void model::end()
{
    captor.release_video();
}