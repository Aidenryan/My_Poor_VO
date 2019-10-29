#include "myslam/camera.h"
#include "myslam/config.h"

namespace myslam
{
    Camera::Camera()
    {
        fx_=Config::get<float>("camera.fx");
        fy_=Config::get<float>("camera.fy");
        cx_=Config::get<float>("camera.cx");
        cy_=Config::get<float>("camera.cy");
        depth_scale_=Config::get<float>("camera.depth_scale");
    }

}