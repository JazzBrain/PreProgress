#include "preprogress.h"
#include "data_io.h"
#include <QDebug>

QString preProgress::getName(){
    return name;
}

void preProgress::processcmd(const V3DPluginArgList &input, V3DPluginArgList &output)
{
     qDebug()<<"--------preProgress::processcmd--------";
    inputfile=((vector<char*> *)(input.at(0).p))->at(0);
    qinputfile=QString(inputfile);
    //qDebug()<<qinputfile;//"/Users/jazz/Downloads/1"

    inputfilelist=getFileNames(qinputfile); //表示文件夹下所有的文件
    //qDebug()<<inputfilelist;//QList("sample.v3draw")

    for(int i=0;i<inputfilelist.size();i++){
        Image4DSimple *nimg;
#ifdef WINDOWS_SYSTEM
        QByteArray ba1=(qinputfile+"\\"+inputfilelist[i]).toLatin1(); //+"\\"+inputfilelist[i]
#endif

#ifdef MACOS_SYSTEM
        QByteArray ba1=(qinputfile+"/"+inputfilelist[i]).toLatin1(); //+"\\"+inputfilelist[i]
#endif

        char *inputimg=ba1.data();

        char inimage[200];//图像路径
        for(int i=0;i<200;i++){
            inimage[i]=inputimg[i];
            if(inputimg[i]=='\0')
                break;
        }

        nimg=cb->loadImage(inimage);//读取图像
        datamem->push_img(nimg);//预处理的数据流
    }

    //qDebug()<<datamem->getimg_cnt();//文件夹下有多少个文件

    outputfile=((vector<char*> *)(output.at(0).p))->at(0);                  //output.at(0)
   // qDebug()<<outputfile;//Users/jazz/Downloads/2

    vector<char *> paras=(*(vector<char*> *)(input.at(1).p));  //img mmf 3 3 3 1 1
    vector<char *> funcparas;

    for(int i=0;i<paras.size();i++){
        if(paras[i][0]>='a'&&paras[i][0]<='z'){         //DataFlowArg[0] is empty.
            DataFlowArg.push_back(funcparas); //存放img mmf
            funcparas.clear();
//             qDebug()<<"--------------paras[i]===================";
//             qDebug()<<paras[i];
            funcparas.push_back(paras[i]);
            continue;
        }
//        qDebug()<<"--------------paras[i]===================1";
//        qDebug()<<paras[i];

        funcparas.push_back(paras[i]);//存放 3 3 3 1 1

        if(i==paras.size()-1)
            DataFlowArg.push_back(funcparas);
    }
    qDebug()<<DataFlowArg[1];//这是img

}


//核心的处理逻辑 调用minmaxfilter
void preProgress::assemblyline()
{
    qDebug()<<"===========preProgress::assemblyline minmaxFilter=============";
    //DataFlowArg.size()是3  0是空的 1是img 2是mmf 3 3 3 1 1
    vector<char*> pluginInputArgList;
    for(int i=1;i<DataFlowArg.size();i++){

        //j==0的时候DataFlowArg[1][0]表示img
        for(int j=1; j<DataFlowArg[i].size(); j++){
            pluginInputArgList.push_back(DataFlowArg[i][j]);  ////这里面存放的是3 3 3 1 1
        }
    }
    preProgress * Preproc= new preProgress(this->cb);
    for(int j=0;j<datamem->getimg_cnt();j++){
        Preproc->minmaxFilter(datamem,pluginInputArgList,j,"mmf");
     }

    for(int j=0;j<datamem->getimg_cnt();j++){
        saveresult(datamem,j);
    }

}






void preProgress::imageProgress(V3DPluginArgList &inputList)
{

}

void preProgress::gaussianfilter()
{
qDebug()<<"===========preProgress::gaussianfilter=============";
    //DataFlowArg.size()是3  0是空的 1是img 2是mmf 3 3 3 1 1
    vector<char*> pluginInputArgList;
    for(int i=1;i<DataFlowArg.size();i++){

        //j==0的时候DataFlowArg[1][0]表示img
        for(int j=1; j<DataFlowArg[i].size(); j++){
            pluginInputArgList.push_back(DataFlowArg[i][j]);  ////这里面存放的是3 3 3 1 1
        }
    }
    preProgress * Preproc= new preProgress(this->cb);
    for(int j=0;j<datamem->getimg_cnt();j++){
        Preproc->gaussianFilter(datamem,pluginInputArgList,j,"gf");
     }

    for(int j=0;j<datamem->getimg_cnt();j++){
        saveresult(datamem,j);
    }
}

void preProgress::laplacianfilter()
{
    qDebug()<<"===========preProgress::laplacianfilter=============";
    vector<char*> pluginInputArgList;
    for(int i=1;i<DataFlowArg.size();i++){
        for(int j=1; j<DataFlowArg[i].size(); j++){
            pluginInputArgList.push_back(DataFlowArg[i][j]);  ////这里面存放的是3 3 3 1 1
        }
    }
    preProgress * Preproc= new preProgress(this->cb);
    for(int j=0;j<datamem->getimg_cnt();j++){
        Preproc->laplacianFilter(datamem,pluginInputArgList,j,"laplacian");
     }

    for(int j=0;j<datamem->getimg_cnt();j++){
        saveresult(datamem,j);
    }
}


void preProgress::saveresult(DataFlow *data, int i)
{
#ifdef WINDOWS_SYSTEM
    QString path = QString(outputfile)+"\\"+inputfilelist[i];
#endif

#ifdef MACOS_SYSTEM
    QString path = QString(outputfile)+"/"+inputfilelist[i];
#endif

    QByteArray ba1=(path).toLatin1(); //+"\\"+inputfilelist[i]
    char *otimg=ba1.data();
    //qDebug()<<inputimg;
    char outpath[200];
    for(int i=0;i<200;i++){
        outpath[i]=otimg[i];
        if(otimg[i]=='\0')
            break;
    }

    cb->saveImage(data->outputimg[i],outpath);
}

void preProgress::initmap()
{
    fnametodll["gf"]="gaussianfilter1.dll";
    fnametodll["app2"]="vn21.dll";
    fnametodll["mmf"]="minMaxfilter.dylib";
    dlltomode["gaussianfilter1.dll"]="Preprocess";
    dlltomode["vn21.dll"]="Computation";
    dlltomode["minMaxfilter.dylib"]= "Preprocess";
}



bool preProgress::minmaxFilter(DataFlow *Predatamem,vector<char *> inputarg,int i,char *funcname)
{
    //通过插件调用minmaxFilter
    V3DPluginArgList pluginInputList, pluginOutputList;
    V3DPluginArgItem Inputimg, InputParam, Outputimg;

    vector<char*> pluginInputArgList;               //input args
    pluginInputArgList.push_back("0");
    pluginInputArgList.push_back("0");
    for(int i=0;i<inputarg.size();i++){
        pluginInputArgList.push_back(inputarg[i]);
    }

    vector<Image4DSimple *> inputimg;               //input imgs
    inputimg.push_back(Predatamem->outputimg[i]);

    vector<Image4DSimple *> outputimg;              //output imgs
    Image4DSimple *otimg=new Image4DSimple();
    outputimg.push_back(otimg);

    Inputimg.type="Inputimg";
    Inputimg.p = (void*)(&inputimg);

    InputParam.type="InputParam";
    InputParam.p = (void*)(&pluginInputArgList);

    Outputimg.type="Outputimg";
    Outputimg.p = (void*)(&outputimg);

    pluginInputList.push_back(Inputimg);
    pluginInputList.push_back(InputParam);
    pluginOutputList.push_back(Outputimg);
    qDebug()<<"minmaxFilter start";
    qDebug()<<"------------------InputParam===================";

#ifdef _ENABLE_MACX_DRAG_DROP_FIX_
    qDebug()<<cb->callPluginFunc("libminMaxfilter.dylib",funcname,pluginInputList, pluginOutputList);

#endif

#ifdef WINDOWS_SYSTEM
    qDebug()<<cb->callPluginFunc("xxxx","mmf",pluginInputList, pluginOutputList);
#endif

    qDebug()<<"minmaxFilter end";
    Predatamem->outputimg[i]=otimg;
    return true;

}

bool preProgress::gaussianFilter(DataFlow *Predatamem, vector<char *> inputarg, int i, char *funcname)
{
    V3DPluginArgList pluginInputList, pluginOutputList;
    V3DPluginArgItem Inputimg, InputParam, Outputimg;

    vector<char*> pluginInputArgList;               //input args
    pluginInputArgList.push_back("0");
    pluginInputArgList.push_back("0");
    for(int i=0;i<inputarg.size();i++){
        pluginInputArgList.push_back(inputarg[i]);
    }

    vector<Image4DSimple *> inputimg;               //input imgs
    inputimg.push_back(Predatamem->outputimg[i]);

    vector<Image4DSimple *> outputimg;              //output imgs
    Image4DSimple *otimg=new Image4DSimple();
    outputimg.push_back(otimg);

    Inputimg.type="Inputimg";
    Inputimg.p = (void*)(&inputimg);

    InputParam.type="InputParam";
    InputParam.p = (void*)(&pluginInputArgList);

    Outputimg.type="Outputimg";
    Outputimg.p = (void*)(&outputimg);

    pluginInputList.push_back(Inputimg);
    pluginInputList.push_back(InputParam);
    pluginOutputList.push_back(Outputimg);
    qDebug()<<"gaussianFilter start";
    qDebug()<<"------------------InputParam===================";

#ifdef _ENABLE_MACX_DRAG_DROP_FIX_
    qDebug()<<cb->callPluginFunc("libgaussianfilter_debug.dylib",funcname,pluginInputList, pluginOutputList);

#endif

#ifdef WINDOWS_SYSTEM
    qDebug()<<cb->callPluginFunc("xxxx","gf",pluginInputList, pluginOutputList);
#endif

    qDebug()<<"gaussianFilter end";
    Predatamem->outputimg[i]=otimg;
    return true;
}

bool preProgress::laplacianFilter(DataFlow *Predatamem, vector<char *> inputarg, int i, char *funcname)
{
    V3DPluginArgList pluginInputList, pluginOutputList;
    V3DPluginArgItem Inputimg, InputParam, Outputimg;

    vector<char*> pluginInputArgList;               //input args
    pluginInputArgList.push_back("0");
    pluginInputArgList.push_back("0");
    for(int i=0;i<inputarg.size();i++){
        pluginInputArgList.push_back(inputarg[i]);
    }

    vector<Image4DSimple *> inputimg;               //input imgs
    inputimg.push_back(Predatamem->outputimg[i]);

    vector<Image4DSimple *> outputimg;              //output imgs
    Image4DSimple *otimg=new Image4DSimple();
    outputimg.push_back(otimg);

    Inputimg.type="Inputimg";
    Inputimg.p = (void*)(&inputimg);

    InputParam.type="InputParam";
    InputParam.p = (void*)(&pluginInputArgList);

    Outputimg.type="Outputimg";
    Outputimg.p = (void*)(&outputimg);

    pluginInputList.push_back(Inputimg);
    pluginInputList.push_back(InputParam);
    pluginOutputList.push_back(Outputimg);
    qDebug()<<"LaplacianFilter start";
    qDebug()<<"------------------InputParam===================";

#ifdef _ENABLE_MACX_DRAG_DROP_FIX_
    qDebug()<<cb->callPluginFunc("libgaussianfilter_debug.dylib",funcname,pluginInputList, pluginOutputList);

#endif

#ifdef WINDOWS_SYSTEM
    qDebug()<<cb->callPluginFunc("xxxx","gf",pluginInputList, pluginOutputList);
#endif

    qDebug()<<"LaplacianFilter end";
    Predatamem->outputimg[i]=otimg;
    return true;
}








void preProgress::getInformation()
{
    //这里可以给用户使用方法
    qDebug("v3d -x gaussian -f gf -i <inimg_file> -o <outimg_file> -p <wx> <wy> <wz> <channel> <sigma>");
}

QString preProgress::getPath(){
    return path;
}
