#ifndef JOYSTICKEXPERIMENTALPLUGIN_H
#define JOYSTICKEXPERIMENTALPLUGIN_H

#include <QObject>
#include "oper_vis_plugin.h"
#include "form.h"
#include "GlfwJoystick.h"
#include "JoystickModel.h"

class JoystickModel;

class JoystickExperimentalPlugin: public OVPlugin
{

public:
    JoystickExperimentalPlugin();

    // OVPlugin interface
public:
    virtual QWidget *getMainWidget() override;
    virtual void setTooltip(const QString &s) override;
    virtual bool start() override;
    virtual void stop() override;
    virtual void updateValue(OVPluginParam *param, QVariant newValue) override;
    void sendValue(OVPluginParam * param, QVariant value);
    void setRollAxe(float value);
    void setPitchAxe(float value);
    void setYawAxe(float value);
    void setThrottleAxe(float value);
    void setJoystickButtons(unsigned value);

public:
    ~JoystickExperimentalPlugin();

private:
    Form * _form = nullptr;
    OVPluginParam * _joystickYaw        = nullptr;
    OVPluginParam * _joystickRoll       = nullptr;
    OVPluginParam * _joystickPitch      = nullptr;
    OVPluginParam * _joystickThrottle   = nullptr;
    OVPluginParam * _joystickNWS        = nullptr;
    OVPluginParam * _joystickButtons    = nullptr;
    QThread _mainThread;
    GlutJoystick * _joy                 = nullptr;
    JoystickModel * _model              = nullptr;

signals:

};

#endif // GLFWPLUGIN_H
