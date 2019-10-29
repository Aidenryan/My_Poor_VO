#include "myslam/config.h"


namespace myslam
{
    void Config::setParammeterFile( const std::string &filename )
    {
        if(config_==nullptr)
        config_= shared_ptr<Config>( new Config);
        //c_str()函数返回一个指向正规C字符串的指针, 内容与本string串相同  
        config_->file_ = cv::FileStorage( filename.c_str(), cv::FileStorage::READ);
        if(config_->file_.isOpened() == false )
        {
            std::cerr<<"parameter file "<<filename<<" doesn't exist"<<std::endl;
            config_->file_.release();
            return;
        }

    }

    Config::~Config()
    {
        if(file_.isOpened())
        file_.release();
    }

    //静态成员变量的定义必须在任何程序块之外；其次调用该变量的时候可以直接用类名加上域解析符“::”加上变量名的形式，
    //这是静态成员变量特有的引用方式；在类外部进行定义的时候static关键字是不需要的。
    shared_ptr<Config> Config::config_=nullptr;
}