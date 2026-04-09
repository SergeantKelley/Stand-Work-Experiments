QT       += widgets core

TARGET = glfw3PluginSample

TEMPLATE = lib

CONFIG += plugin c++11

LIBS += -L$$PWD/lib -lovplugins
LIBS += -lGL -lGLU -lglfw -lGLEW -glm

DESTDIR = /home/student/.oper_vis/plugins/

SOURCES += form.cpp \
           glfw3PluginSample.cpp \
           Window.cpp \
           Sphere.cpp \
           Shader.cpp \
           Pyramid.cpp \
           Cube.cpp \
           Model_Controller.cpp

HEADERS += oper_vis_plugin.h \
           form.h \
           glfw3PluginSample.h \
           Window.h \
           Sphere.h \
           Shader.h \
           Pyramid.h \
           Cube.h \
           Model_Controller.h

RESOURCES += \
    resource.qrc

FORMS += \
    form.ui

