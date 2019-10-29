#include "myslam/map.h"

namespace myslam
{
    void Map::insertKeyFrame( Frame::Ptr frame )
    {
        cout<<"Key Frame size :"<<keyframe_.size()<<endl;
        //如果该帧id为容器末尾，则在关键帧中插入该帧
        if(keyframe_.find(frame->id_)==keyframe_.end())
        {
            keyframe_.insert( make_pair( frame->id_, frame));
        }
        else
        {
            keyframe_[frame->id_] = frame;
        }
        
    }

    void Map::insertMapPoint(MapPoint::Ptr map_point)
    {
        if(map_point_.find(map_point->id_) == map_point_.end())
        {
            map_point_.insert( make_pair(map_point->id_, map_point));
        }
        else
        {
            map_point_[map_point->id_] = map_point;
        }        
    }
}