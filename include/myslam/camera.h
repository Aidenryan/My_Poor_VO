#ifndef CAMERA_H
#define CAMERA_H

/*
双引号可以代替尖括号，如果加载的是系统头文件就使用尖括号，系统会自动到标准的库中找头文件，
如果是双引号系统先到当前项目中找头文件，找到结束，找不到就去系统库中找，自定义的头文件建议使用双引号的形式
*/

#include "myslam/common_include.h"

namespace myslam
{
//小孔 RGBD 相机模型
class Camera
{
public:
    //定义camera类的智能指针
    typedef std::shared_ptr<Camera> Ptr;
    //相机内参
    float fx_, fy_, cx_, cy_, depth_scale_; 
    
    //默认构造函数
    Camera();
    //参数初始化表
    Camera(float fx, float fy, float cx, float cy, float depth_scale=0):
    fx_(fx), fy_(fy), cx_(cx), cy_(cy), depth_scale_(depth_scale) {}


    //坐标转换： 世界 相机 像素
    //const + 引用说明 参数只能在外部进行改变 不能函数内部改变
    inline Vector3d world2camera( const Vector3d &p_w, const SE3& T_c_w)
    {
        return T_c_w*p_w;
    }

    inline Vector3d camera2world( const Vector3d& p_c, const SE3& T_c_w )
    {
        return T_c_w.inverse()*p_c;
    }

    inline Vector2d camera2pixel( const Vector3d& p_c )
    {
        return Vector2d( cx_ + fx_ * p_c(0,0) / p_c(0,2), 
                         cy_ + fy_ * p_c(0,1) / p_c(0,2) );
    }

    inline Vector3d pixel2camera( const Vector2d& p_p, double depth=1 )
    {
        return Vector3d( ( p_p(0,0) - cx_ ) * depth / fx_ ,
                         ( p_p(0,1) - cy_ ) * depth / fy_ ,
                         depth );
    }

    inline Vector3d pixel2world ( const Vector2d& p_p, const SE3& T_c_w, double depth=1 )
    {
        
        return camera2world( pixel2camera(p_p, depth), T_c_w);
    }

    inline Vector2d world2pixel ( const Vector3d& p_w, const SE3& T_c_w )
    {
        return camera2pixel( world2camera( p_w, T_c_w) );
    }
};

}































#endif