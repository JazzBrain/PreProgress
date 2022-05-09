

V3DMAINPATH =  /Users/jazz/Desktop/v3d_new/v3d_external/v3d_main
V3DPLUGINS = /Users/jazz/Desktop/v3d_new/vaa3d_tools/released_plugins/v3d_plugins

TEMPLATE	= lib
CONFIG	+= qt plugin warn_off
QT += widgets
macx{
    DEFINES += MACOS_SYSTEM
    #dragdropfix
    DEFINES += _ENABLE_MACX_DRAG_DROP_FIX_
}

win32{
    CONFIG += console
    DEFINES += WINDOWS_SYSTEM
    DEFINES += __ALLOW_VR_FUNCS__

}


HEADERS += $$V3DMAINPATH/basic_c_fun/v3d_interface.h \
    data_io.h \
    preTools.h \
    superPlugin.h

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

VAA3DPATH = /Users/jazz/Desktop/v3d_new/v3d_external
RUNV3DPATH = /Users/jazz/Desktop/vaa3dapp
INCLUDEPATH	+= $$VAA3DPATH/v3d_main/basic_c_fun
INCLUDEPATH	+= $$VAA3DPATH/v3d_main/v3d
INCLUDEPATH	+= $$VAA3DPATH/v3d_main/common_lib/include
INCLUDEPATH	+= $$V3DMAINPATH/plugin_loader
INCLUDEPATH	+= $$V3DMAINPATH/3drenderer
INCLUDEPATH     += $$V3DMAINPATH

INCLUDEPATH	+= $$V3DMAINPATH/terafly

#INCLUDEPATH += $$V3DPLUGINS/gsdt/main
#INCLUDEPATH += $$V3DPLUGINS/gsdt

HEADERS += $$V3DMAINPATH/basic_c_fun/basic_memory.h
#HEADERS += $$V3DPLUGINS/gsdt/common_value.h
#HEADERS += $$V3DPLUGINS/gaussianfilter/gaussianfilterplugin.h
#HEADERS += $$V3DPLUGINS/gsdt/gsdt_plugin.h
#HEADERS	+= $$V3DPLUGINS/gsdt/gsdt_func.h
#HEADERS += $$V3DPLUGINS/gsdt/common_dialog.h


SOURCES += data_io.cpp \
        preTools.cpp \
        superPlugin.cpp
#SOURCES += $$V3DMAINPATH/basic_c_fun/v3d_message.cpp
#SOURCES += $$V3DMAINPATH/basic_c_fun/basic_memory.cpp
#SOURCES	+= $$V3DPLUGINS/gsdt/gsdt_func.cpp


SOURCES += preprogress.cpp



TARGET	= $$qtLibraryTarget(SuperPlugin)
DESTDIR	= /Users/jazz/Desktop/vaa3dapp/plugins/SuperPlugin_ljs/





