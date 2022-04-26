#ifndef PREPROGRESS_H
#define PREPROGRESS_H


#include "../gaussianfilter/gaussianfilterplugin.cpp"
#include "../gsdt/gsdt_func.cpp"
#include "v3d_interface.h"

///
/// 使用方法:通过该类声明一个对象，构造函数中需要三个参数，插件名称，图片路径，以及一个V3DPluginCallback类型的对象
///
class preProgress {
private:
    QString name;//gaussianfilter
    QString path;
    V3DPluginArgList input;
    V3DPluginArgList output;
    Image4DSimple* image;
    //float *outimg;
public:
    //通过动态库的名字以及路径进行初始化
    preProgress(QString name, QString path, V3DPluginCallback &cb) {
        this->name = name;
        this->path = path;
        char *ch = path.toLatin1().data();
        image = cb.loadImage(ch);
    };


    void imageProgress(V3DPluginArgList &);
    void getInformation();
    QString getPath();
    QString getName();


    void callBack();//根据插件动态库的path进行插件的调用
};



#endif // PREPROGRESS_H
