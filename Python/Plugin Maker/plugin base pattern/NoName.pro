QT       += widgets core

TARGET = NoName

TEMPLATE = lib

CONFIG += plugin c++11

LIBS += -L$$PWD/lib -lovplugins

SOURCES += form.cpp \
           NoName.cpp

HEADERS += oper_vis_plugin.h \
           form.h \
           NoName.h

RESOURCES += \
    resource.qrc

FORMS += \
    form.ui

