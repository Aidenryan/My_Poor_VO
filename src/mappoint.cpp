#include "myslam/mappoint.h"

namespace myslam
{
    MapPoint::MapPoint()
    :id_(-1), pos_(Vector3d(0,0,0)), norm_(Vector3d(0,0,0)),observed_times_(0) {}

    MapPoint::MapPoint( long id, Vector3d position, Vector3d norm )
    :id_(id), pos_(position), norm_(norm),observed_times_(0) {}

    MapPoint::Ptr MapPoint::createMapPoint()
    {
        //这里用static的原因是 因为静态局部变量在下次函数调用是，它会保持上次的值
        static long factory_id = 0;
        return MapPoint::Ptr( new MapPoint(factory_id++, Vector3d(0,0,0), Vector3d(0,0,0) ));
    }
}