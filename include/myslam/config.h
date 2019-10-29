#ifndef CONFIG_H
#define CONFIG_H

#include "myslam/common_include.h"

namespace myslam
{
class Config
{
private:
    static std::shared_ptr<Config> config_;
    cv::FileStorage file_;
    
    Config(){}
public:
    //析构函数
    ~Config();
    //设定配置文件
    //静态成员函数只能访问静态成员变量，而不能访问非静态成员变量
    //http://www.weixueyuan.net/view/6349.html
    //声明加了static 定义时候不用static
    static void setParammeterFile(const std::string &filename);

    //获取参数值
    template <typename T >
    static T get(const std::string &key)
    {
        return T (Config::config_->file_[key]);
    }
};
}



















#endif