#ifndef GLFW3PLUGINSAMPLE_H
#define GLFW3PLUGINSAMPLE_H

#include <QObject>
#include <QThread>
#include <QMessageBox>

#include "oper_vis_plugin.h"
#include "form.h"
#include"Window.h"
#include "Model_Controller.h"

class Model;
class Controller;

class glfw3PluginSample: public OVPlugin
{

public:
    glfw3PluginSample();
    ~glfw3PluginSample();

    // OVPlugin interface
public:
    virtual QWidget *getMainWidget() override;
    virtual void setTooltip(const QString &s) override;
    virtual bool start() override;
    virtual void stop() override;
    virtual void updateValue(OVPluginParam *param, QVariant newValue) override;

public:
    void setPositionX(float X);

private:
    Form * _form                = nullptr;
    QThread _glWindowThread;

private:
    OVPluginParam * _greenParam = nullptr;
    OVPluginParam * _ngAngle    = nullptr;
    OVPluginParam * _Xcoord     = nullptr;
    Model * _model              = nullptr;
    Controller * _controller    = nullptr;


signals:

};

#endif // NO_NAME
