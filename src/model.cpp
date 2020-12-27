#include "model.h"
#include "../gui/cvui.h"

//initialize model
model::model(std::string video, std::string target)
{
    pool.create_threads(5);
    is_start = false;
    d_type = detector_t::SURF;
    interval = 10;
    img_object_rgb = imread(target, IMREAD_ANYCOLOR);
    processor.convert_color(img_object_rgb, img_object, COLOR_RGB2GRAY);
    captor.capture_video(video);
}

//detect one frame
void model::detect_frame()
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
    advertisement_detecor detector(d_type);
    detector.set_filter_distance_ratio(0.6);
    std::vector<Point2f> good_points_object, good_points_scene;
    detector.detect(img_object, img_scene, good_points_object, good_points_scene);

    //transform coordinate from object to scene
    transformer transformer;
    std::vector<Point2f> corner_scene(4);
    transformer.transform_coordinate(img_object, img_scene, good_points_object, good_points_scene, corner_scene);

    //draw bounding box on detected object
    {
        std::unique_lock<std::mutex> lock(output_imgs_mutex);
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
    detector_gui gui;
    gui.create();
    while (!gui.get_start_state())
    {
        Mat temp = cv::Mat(cv::Size(800, 590), CV_8UC3);
        temp = cv::Scalar(100, 100, 100);
        interval = gui.get_interval();
        gui.refresh(temp);
        gui.show();
    }
    is_start = true;
    d_type= (detector_t)gui.get_mode_state();
    
    while (true)
    {
        if (!output_imgs.empty())
        {
            gui.refresh(output_imgs.at(0));
            output_imgs.erase(output_imgs.begin());
            gui.show();
        }

        if (!gui.get_start_state())
        {
            is_start = false;
            return;
        }
    }
}

//start model
void model::start()
{
    std::function<void()> play_frame = std::bind(&model::play_frame, this);
    pool.enqueue_task(play_frame);
    while (!is_start){}
    for (int i = 0; i < captor.get_frame_count(); i = i + interval)
    {
        if (is_start)
        {
            std::function<void()> exe_fun = std::bind(&model::detect_frame, this);
            pool.enqueue_task(exe_fun);
        }
        else
        {
            return;
        }
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
    pool.~thread_pool();
}