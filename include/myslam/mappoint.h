#ifndef MAPPOINT_H
#define MAPPOINT_H

#include "myslam/common_include.h"
namespace myslam
{
class Frame;
class MapPoint
{
public:
    typedef std::shared_ptr < MapPoint > Ptr;
    unsigned long id_; //ID
    Vector3d pos_;     //世界坐标系下的坐标
    Vector3d norm_;    // Normal of viewing direction 
    // Mat descriptor_;   //描述子，但是这里我用光流法，是没有用的
    int observed_times_;  // being observed by feature matching algo.
    int matched_times_;  //being an inliner

    MapPoint();
    MapPoint(long id, Vector3d position, Vector3d norm);

    static MapPoint::Ptr createMapPoint();
};
}
#endif