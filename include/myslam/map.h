#ifndef MAP_H
#define MAP_H

#include "myslam/common_include.h"
#include "myslam/frame.h"
#include "myslam/mappoint.h"

namespace myslam
{
class Map
{
public:
    typedef std::shared_ptr<Map> Ptr;
    //id + 指针
    unordered_map<unsigned long, MapPoint::Ptr > map_point_;
    unordered_map<unsigned long, Frame::Ptr > keyframe_;

    Map() {}

    void insertKeyFrame( Frame::Ptr frame);
    void insertMapPoint( MapPoint::Ptr map_point );

};
}
#endif