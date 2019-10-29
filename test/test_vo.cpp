//光流法写的小视觉里程计10.29
#include <fstream>
#include <iostream>
#include <boost/timer.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "myslam/config.h"
#include "myslam/visual_odometry.h"

using namespace std;

int main( int argc, char** argv )
{
    if ( argc !=2)
    {
        cout<<"usage: test_vo parameter_file"<<endl;
    }

    myslam::Config::setParammeterFile( argv[1] );
    myslam::VisualOdometry::Ptr vo (new myslam::VisualOdometry);

    string dataset_dir = myslam::Config::get<string>("dataset_dir");
    cout<<"dataset: "<<dataset_dir<<endl;
    ifstream fin ( dataset_dir+"/associate.txt");

    if(!fin)
    {
        cout<<"please generate the associate file called associate.txt!"<<endl;
        return 1;
    }

    vector<string> rgb_files, depth_files;
    vector<double> rgb_times, depth_times;

    while( !fin.eof() )
    {
        string rgb_time, rgb_file, depth_time, depth_file;
        fin>>rgb_time>>rgb_file>>depth_time>>depth_file;
        //atof 将字符串转为double类型
        rgb_times.push_back ( atof ( rgb_time.c_str() ) );
        depth_times.push_back ( atof ( depth_time.c_str() ) );
        rgb_files.push_back ( dataset_dir+"/"+rgb_file );
        depth_files.push_back ( dataset_dir+"/"+depth_file );

        if ( fin.good()== false )
        break;
    }

    myslam::Camera::Ptr camera (new myslam::Camera);

    cout<<"read total "<< rgb_files.size()<<" entries"<<endl;

    for (int i=0; i<rgb_files.size(); i++)
    {
        cout<<"循环次数："<<i<<endl;
        Mat color = cv::imread( rgb_files[i]);
        Mat depth = cv::imread( depth_files[i], -1 );
        if(color.data==nullptr || depth.data==nullptr )
        {
            break;
        }

        myslam::Frame::Ptr pFrame = myslam::Frame::createFrame();
        pFrame->camera_ = camera;
        pFrame->color_ = color;
        pFrame->depth_ = depth;
        pFrame->time_stamp_ = rgb_times[i];

        boost::timer timer;

        vo->addFrame(pFrame);
        cout<<"VO costs time:"<<timer.elapsed()<<endl;

        if( vo->state_==myslam::VisualOdometry::LOST)
            break;

        //SE3 
        cv::imshow("image", color );
        cv::waitKey(1000);
        if(i==6)
        return 0;
    }

    return 0;
}