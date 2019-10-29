/*
C++接口：
void calcOpticallFlowPyrLK (InuputArray prevImg, InputArray nextImg, InputArray prevPts, InputOutputArray
nextPts, OutputArray status, OutputArray err, Size winSize = Size(21,21), int maxLevel = 3, TermCriteria
criteria = TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, 0.01), int flags = 0, double minEigThreshold = 1e-4);
-prevImg: 深度为8位的前一帧图像或金字塔图像。
-nextImg：和prevImg有相同的大小和类型，后一帧图像或金字塔。
-prevPts：计算光流所需要的输入2D点矢量，点坐标必须是单精度浮点数。
-nextPts：输出2D点矢量(也是单精度浮点数坐标)，点矢量中包含的是在后一帧图像上计算得到的输入特征新位置。
-status：输出状态矢量(元素是无符号char类型，uchar)，如果相应特征的流发现则矢量元素置为1，否则，为0。
-err：输出误差矢量。
-winSize：每个金字塔层搜索窗大小。
-maxLevel：金字塔层的最大数目；如果置0，金字塔不使用(单层)；如果置1，金字塔2层，等等以此类推。
-criteria：指定搜索算法收敛迭代的类型
-minEigTheshold：算法计算的光流等式的2x2常规矩阵的最小特征值。
*/

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/tracking.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <algorithm>
#include <boost/timer.hpp>

#include "myslam/visual_odometry.h"
#include "myslam/config.h"

namespace myslam
{
    VisualOdometry::VisualOdometry():
    state_(INITIALIZING), ref_(nullptr), curr_(nullptr), map_( new Map), num_lost_(0), num_inliers_(0)
    {
        num_of_features_    = Config::get<int> ("number_of_features");
       // scale_factor_       = Config::get<double> ("scale_factor");
       //level_pyramid_      = Config::get<int> ( "level_pyramid" );
        match_ratio_        = Config::get<float> ( "match_ratio" );
        max_num_lost_       = Config::get<float> ( "max_num_lost" );
        min_inlier_        = Config::get<int> ( "min_inliers" );
        key_frame_min_rot   = Config::get<double> ( "keyframe_rotation" );
        key_frame_min_trans = Config::get<double> ( "keyframe_translation" );
        fast_ = cv::FastFeatureDetector::create ( num_of_features_);
        //cout<<"需要提取的特征数量：  "<<num_of_features_<<endl;
    }

    VisualOdometry::~VisualOdometry()
   {

   } 

    bool VisualOdometry::addFrame( Frame::Ptr frame)
    {
        cout<<"状态"<<state_<<endl;
        switch( state_)
        {
            case INITIALIZING:
            {
                state_ = OK;
                curr_ = frame;
                //ref_= frame;
                map_->insertKeyFrame( frame );
                //cv::imshow("image", curr_->color_ );
                //cv::waitKey(1000);
                extractKeyPoint();
                exchangemsg();
                break;
            }
            case OK:
            {
                curr_ = frame;
                //extractKeyPoint();
                poseEstimation();
                exchangemsg();
                break;
            }
            case LOST:
            {
                cout<<"vo has lost."<<endl;
                break;
            }
        }
        return true;
    }

    void VisualOdometry::extractKeyPoint()
    {
        //fast_->detect(curr_->color_, keypoint_curr_);
        fast_->detect(curr_->color_, keypoint_curr_);
        cout<<"keypoint_curr_特征点数量:  "<<keypoint_curr_.size()<<endl;
        for (auto kp : keypoint_curr_)
            curr_->keypoints.push_back(kp.pt);
        cout<<"特征点数量:  "<<curr_->keypoints.size()<<endl;
    }

    /*void VisualOdometry::setRef3DPoints()
    {
        pts_3d_ref_.clear();
        for( size_t i = 0; i<keypoint_curr_.size(), i++)
        {
            double d = ref_->findDepth(keypoint_curr_[i]);  
            if(d>0)
            {
                Vector3d p_cam = ref_->camera_->pixel2camera( Vector2d(keypoint_curr_[i].pt.x, keypoint_curr_[i].pt.y), d);
                pts_3d_ref_.push_back( cv::Point3d(p_cam(0,0), p_cam(1,0), p_cam(2,0) ) );
            }
        }
    }*/

    void VisualOdometry::poseEstimation()
    {
        curr_->focal_= Config::get<double>("camera.fx");
        double xc=Config::get<double>("camera.cx: 325.1");
        double yc=Config::get<double>("camera.cy: 325.1");
        curr_->pp_  = cv::Point2d(xc, yc);
        cv::Mat R,t, E, mask;
        vector<unsigned char> status;
        vector<float> error; 
        cv::calcOpticalFlowPyrLK( ref_->color_ , curr_->color_ , ref_->keypoints, curr_->keypoints, status, error );
        E = cv::findEssentialMat(curr_->keypoints, ref_->keypoints, curr_->focal_ , curr_->pp_, cv::RANSAC, 0.999, 1.0, mask);
        cv::recoverPose(E, curr_->keypoints, ref_->keypoints, R, t, curr_->focal_ , curr_->pp_, mask);
        cout<<"R= "<<endl<<R<<endl;
    }

    void VisualOdometry::exchangemsg()
    {
        cout<<"begin"<<endl;
        //ref_->color_ = curr_->color_;
        //ref_->keypoints.clear();
        //for(auto kp : curr_->keypoints )
         //   ref_->keypoints.push_back(kp);
         ref_=curr_;
        cout<<"当前帧特征点数量:  "<<curr_->keypoints.size()<<endl;
        cout<<"参考帧特征点数量:  "<<ref_->keypoints.size()<<endl;
        //curr_->keypoints.clear();
        cout<<"end"<<endl;
        //cv::imshow("image", ref_->color_ );
        //cv::waitKey(1000);
    }

    //void VisualOdometry::featureTracking()
}