QT       += widgets core

TARGET = StandPluginSample

TEMPLATE = lib

CONFIG += plugin c++11

LIBS += -L$$PWD/lib -lovplugins

SOURCES += \
           StandPluginSample.cpp \
    form.cpp \
    Model_Controller.cpp

HEADERS += oper_vis_plugin.h \
           StandPluginSample.h \
    form.h \
    Model_Controller.h

RESOURCES += \
    resource.qrc

FORMS += \
    form.ui

