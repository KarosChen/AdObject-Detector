#include "model.h"

//initialize model
model::model()
{
    pool.create_threads(5);
    is_detect = true;
    interval = 10;
    img_object_rgb = imread("C:/Users/user/Desktop/object3.png", IMREAD_ANYCOLOR);
    processor.convert_color(img_object_rgb, img_object, COLOR_RGB2GRAY);
    captor.capture_video("C:/Users/user/Desktop/test_video.mp4");
}

//detect one frame
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
                if (captor.read_frame(img_scene_rgb))
                {
                    img_scene_rgbs.emplace_back(img_scene_rgb);
                }
            }
        }

        //resize image and convert color to gray
        Mat img_scene;
        processor.set_scale_factor(0.5);
        processor.resize_image(img_scene_rgbs.front(), img_scene);
        processor.convert_color(img_scene, img_scene, COLOR_RGB2GRAY);
        
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
            processor.draw_bouding_box(img_scene_rgbs[i], corner_scene);
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
            frame_num++;
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

//release video and other objects
void model::end()
{
    captor.release_video();
}