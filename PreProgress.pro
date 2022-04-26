

#TEMPLATE = SUBDIRS
#SUBDIRS = /Users/jazz/Desktop/v3d_new/vaa3d_tools/released_plugins/v3d_plugins/gaussianfilter \
QT += widgets

V3DMAINPATH =  /Users/jazz/Desktop/v3d_new/v3d_external/v3d_main
V3DPLUGINS = /Users/jazz/Desktop/v3d_new/vaa3d_tools/released_plugins/v3d_plugins

TEMPLATE	= lib
CONFIG	+= qt plugin warn_off
#include($$V3DMAINPATH/../vaa3d_tools/released_plugins/v3d_plugins/gaussianfilter/gaussianfilter.pro)
#include($$V3DMAINPATH/../vaa3d_tools/released_plugins/v3d_plugins/gsdt/gsdt.pro)
#/Users/jazz/Desktop/v3d_new/vaa3d_tools/released_plugins/v3d_plugins/gsdt/gsdt.pro


INCLUDEPATH	+= $$V3DMAINPATH/basic_c_fun
INCLUDEPATH += $$V3DMAINPATH/common_lib/include

SOURCES += \
        main.cpp \
        preprogress.cpp

HEADERS += $$V3DMAINPATH/basic_c_fun/v3d_interface.h

HEADERS += \
    preprogress.h


macx{
    LIBS += -L$$V3DMAINPATH/common_lib/lib_mac64 -lv3dnewmat
}

win32{
    LIBS += -L$$V3DMAINPATH/common_lib/mingw -lv3dnewmat
}

unix:!macx {
    LIBS += -L$$V3DMAINPATH/jba/c++ -lv3dnewmat
}



INCLUDEPATH	+= $$V3DMAINPATH/basic_c_fun
INCLUDEPATH	+= $$V3DMAINPATH/terafly
INCLUDEPATH += $$V3DMAINPATH/common_lib/include
INCLUDEPATH += $$V3DPLUGINS/gsdt/main
INCLUDEPATH += $$V3DPLUGINS/gsdt

HEADERS += $$V3DMAINPATH/basic_c_fun/basic_memory.h
HEADERS += $$V3DPLUGINS/gsdt/common_value.h
HEADERS += $$V3DPLUGINS/gaussianfilter/gaussianfilterplugin.h
#HEADERS += $$V3DPLUGINS/gsdt/gsdt_plugin.h
HEADERS	+= $$V3DPLUGINS/gsdt/gsdt_func.h
HEADERS += $$V3DPLUGINS/gsdt/common_dialog.h


SOURCES += $$V3DPLUGINS/gaussianfilter/gaussianfilterplugin.cpp
SOURCES += $$V3DMAINPATH/basic_c_fun/v3d_message.cpp
SOURCES += $$V3DMAINPATH/basic_c_fun/basic_memory.cpp
#SOURCES += $$V3DPLUGINS/gsdt/gsdt_plugin.cpp
SOURCES	+= $$V3DPLUGINS/gsdt/gsdt_func.cpp


#TARGET        = $$qtLibraryTarget(gaussianfilter)
#DESTDIR       = /Users/jazz/Desktop/vaa3dapp/plugins/image_filters/Gaussian_Filter







