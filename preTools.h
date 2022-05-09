#ifndef PRETOOLS_H
#define PRETOOLS_H


#include "preprogress.h"

class preTools {
private:
    preProgress *pre;
    V3DPluginCallback2 *cb;
public:
    preTools(V3DPluginCallback2* cb1,const V3DPluginArgList &input, V3DPluginArgList &output){
        this->cb = cb1;
        pre = new preProgress(this->cb);
        pre->processcmd(input,output);
    }
    void minmaxFilter();
    void guassianFilter();
    void laplacianFilter();
};






#endif // PRETOOLS_H
