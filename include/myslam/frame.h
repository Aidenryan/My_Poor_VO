
#ifndef FRAME_H
#define FRAME_H

#include "myslam/common_include.h"
#include "myslam/camera.h"


namespace myslam
{
class Mappoint;

class Frame
{
public:
    typedef std::shared_ptr <Frame> Ptr;
    unsigned long id_; //这帧的id
    double time_stamp_; //帧被记录时间
    SE3    T_c_w_;     //世界坐标系到相机坐标系的变化
    Camera::Ptr  camera_; //小孔相机模型
    Mat          color_, depth_; //
    vector<cv::Point2f> keypoints;//Point2f的关键点

public:
    Frame();
    ~Frame();
    Frame( long id, double time_stamp=0, SE3 T_c_w=SE3(), Camera::Ptr camera=nullptr, Mat color=Mat(), Mat depth=Mat() );

    static Frame::Ptr createFrame();

    //在深度图中寻找深度
    double findDepth( const cv::KeyPoint &kp);

    double focal_;//!<相机焦距
	cv::Point2d pp_; //!<相机中心点

    //获取相机中心
    //常成员函数可以访问类中的任何成员变量，但是不能修改任何成员变量。
    //const成员函数是不能调用类中非const成员函数的
    Vector3d getCamCenter() const
    {
        return T_c_w_.inverse().translation();
    }

    //检查point 是否在这帧中
    bool isInFrame( const Vector3d &pt_world);
};


#endif



























}