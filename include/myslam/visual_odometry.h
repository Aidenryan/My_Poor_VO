#ifndef VISUALODOMETRY_H
#define VISUALODOMETRY_H

#include "myslam/common_include.h"
#include "myslam/map.h"


namespace myslam
{
class VisualOdometry
{
public:
    typedef std::shared_ptr<VisualOdometry> Ptr;

    enum VOState
    {
        INITIALIZING=-1,
        OK=0,
        LOST
    };

    VOState state_;  //里程计当前状态
    Map::Ptr map_;  //地图
    Frame::Ptr ref_; //参考帧
    Frame::Ptr curr_; //当前帧

    

    cv::Ptr<cv::FastFeatureDetector> fast_; //fast detector 原来是orb
    vector<cv::Point3f>  pts_3d_ref_;  //3D点在参考帧
    vector<cv::KeyPoint>  keypoint_curr_; //keypointx在当前帧

    //   Mat  descriptors_curr_;  // descriptor in current frame 
    //   Mat   descriptors_ref_;   // descriptor in reference frame 
    vector<cv::DMatch>   feature_matches_;

    SE3 T_c_r_estimated_; //当前帧的位姿估计
    int num_inliers_;    //icp中内点数量
    int num_lost_;        //number of lost times

    //参数
    int num_of_features_; //特征点数量
    //double scale_factor_;  //图像金字塔中的scale
    //int level_pyramid_;   //金字塔层数
    float match_ratio_;  //挑选好的匹配
    int max_num_lost_;   //最大连续跟丢次数
    int min_inlier_;    //最小内点数

    double key_frame_min_rot;
    double key_frame_min_trans;

public://函数
    VisualOdometry();
    ~VisualOdometry();

    bool addFrame(Frame::Ptr frame);

protected:
    //内部操作
    void extractKeyPoint();
    //void computeDescriptors(); 
   // void featureTracking();
    void poseEstimation();
    //void setRef3DPoints();
    void exchangemsg();
    //void addKeyFrame();
   // bool checkEstimatePose();
   // bool checkKeyFrame();
    
};
}
#endif