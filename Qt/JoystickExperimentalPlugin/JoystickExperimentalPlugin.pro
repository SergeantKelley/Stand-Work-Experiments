QT       += widgets core

TARGET = JoystickExperimentalPlugin

TEMPLATE = lib

CONFIG += plugin c++11

LIBS += -L$$PWD/lib -lovplugins
LIBS+= -lGL -lGLU -lglut -lglfw -glew

SOURCES += form.cpp \
           JoystickExperimentalPlugin.cpp \
           JoystickModel.cpp \
           GlfwJoystick.cpp

HEADERS += oper_vis_plugin.h \
           form.h \
           JoystickExperimentalPlugin.h \
           JoystickModel.h \
           GlfwJoystick.h

RESOURCES += \
    resource.qrc

FORMS += \
    form.ui

