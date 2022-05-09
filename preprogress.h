#ifndef PREPROGRESS_H
#define PREPROGRESS_H


//#include "../gaussianfilter/gaussianfilterplugin.cpp"
//#include "../gsdt/gsdt_func.cpp"
//#include "../minMaxfilter/minMaxfilterplugin.cpp"
#include "v3d_interface.h"
#include <vector>
#include <unordered_map>

using namespace std;
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
    V3DPluginCallback2* cb;
    //float *outimg;
    DataFlow *datamem;//存放数据流在内存中

    char * inputfile;           // can be optimized
    char * outputfile;

    vector<vector<char *>> DataFlowArg;//命令行的参数
    QString qinputfile;
    QStringList inputfilelist;
    unordered_map<QString,QString> fnametodll;
    unordered_map<QString,QString> dlltomode;


public:
    //通过动态库的名字以及路径进行初始化
    preProgress(V3DPluginCallback2 *cb) { //这个肯定需要在插件里面使用的
        name = "";
        path = "";
        this->cb = cb;
        datamem = new DataFlow();
    }

    preProgress(QString name, QString path, V3DPluginCallback2 *cb) {
        this->name = name;
        this->path = path;
        datamem = new DataFlow();
        char *ch = path.toLatin1().data();
        this->cb = cb;
        image = cb->loadImage(ch);
    };


    //调用minmaxFilter插件
    bool minmaxFilter(DataFlow *Predatamem,vector<char *> inputarg,int i,char *funcname);
    bool gaussianFilter(DataFlow *Predatamem,vector<char *> inputarg,int i,char *funcname);
    bool laplacianFilter(DataFlow *Predatamem,vector<char *> inputarg,int i,char *funcname);
    DataFlow* getData(){
        return datamem;//获取内存中的数据流
    }
    void getInformation();
    QString getPath();
    QString getName();




    void processcmd(const V3DPluginArgList & input, V3DPluginArgList & output);//读取图像
    void assemblyline();//核心的处理逻辑
    void saveresult(DataFlow* data,int i);//保存结果
    void initmap();
    void imageProgress(V3DPluginArgList &);
    void gaussianfilter();
    void laplacianfilter();

};



#endif // PREPROGRESS_H
