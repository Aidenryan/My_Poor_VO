#ifndef COMMON_INCLUDE_H
#define COMMON_INCLUDE_H

//for eigen3
#include <Eigen/Core>
#include <Eigen/Geometry>
using Eigen::Vector2d;
using Eigen::Vector3d;

//for sophus
#include <sophus/se3.h>
#include <sophus/so3.h>
using Sophus::SE3;
using Sophus::SO3;

//for cv
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
using cv::Mat;
using namespace cv;

//for std;
#include <vector>
#include <memory>
#include <list>
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

#endif