#include "preprogress.h"

#include <QDebug>

QString preProgress::getName(){
    return name;
}


//核心的处理逻辑
void preProgress::imageProgress(V3DPluginArgList &)
{
    if(this->name == "gaussianfilter") {
        V3DLONG in_sz[4];
        in_sz[0] = image->getXDim();
        in_sz[1] = image->getYDim();
        in_sz[2] = image->getZDim();
        in_sz[3] = image->getCDim();
        unsigned int Wx=7, Wy=7, Wz=3, c=1;
        float sigma = 1.0;
        float *outimg = 0;
        unsigned char* data1d = image->getRawData();
        switch (image->getDatatype()) {
            case V3D_UINT8: gaussian_filter(data1d, in_sz, Wx, Wy, Wz, c, sigma, outimg); break;
            case V3D_UINT16: gaussian_filter((unsigned short int *)data1d, in_sz, Wx, Wy, Wz, c, sigma, outimg); break;
            case V3D_FLOAT32: gaussian_filter((float *)data1d, in_sz, Wx, Wy, Wz, c, sigma, outimg);break;
            default: v3d_msg("Invalid data type. Do nothing."); return;
        }
        //处理好的结果保存在了outimg中，为之后构建重建库作准备
    }

    else if(this->name == "gsdt") {
        switch(image->getDatatype())
        {
            int bkg_thresh = 0, cnn_type = 2, channel = 0, z_thickness = 1.0;
            V3DLONG sz0 = image->getXDim();
            V3DLONG sz1 = image->getYDim();
            V3DLONG sz2 = image->getZDim();
            V3DLONG sz3 = image->getCDim();
            float * phi = 0;
            unsigned char * inimg1d = image->getRawDataAtChannel(channel);

        }
    }





}

void preProgress::getInformation()
{
    //这里可以给用户使用方法
    qDebug("v3d -x gaussian -f gf -i <inimg_file> -o <outimg_file> -p <wx> <wy> <wz> <channel> <sigma>");
}

QString preProgress::getPath(){
    return path;
}
