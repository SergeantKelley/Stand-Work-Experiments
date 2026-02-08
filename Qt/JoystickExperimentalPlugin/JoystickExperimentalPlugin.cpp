#include "JoystickExperimentalPlugin.h"



JoystickExperimentalPlugin::JoystickExperimentalPlugin()
{
    setName("JoystickExperimentalPlugin");
    icons.addPixmap(QPixmap(":/icon1"), QIcon::Normal, QIcon::On);
    _joy = new GlutJoystick();

    _joystickNWS = makeParam("main", "JOYSTICK_NWS");
    _joystickPitch = makeParam("main", "JOYSTICK_PITCH");
    _joystickRoll = makeParam("main", "JOYSTICK_ROLL");
    _joystickYaw = makeParam("main", "JOYSTICK_YAW");
    _joystickThrottle = makeParam("main", "JOYSTICK_THROTTLE");
    _joystickButtons = makeParam("main", "JOYSTICK_BUTTONS");
}

QWidget *JoystickExperimentalPlugin::getMainWidget()
{
    return _form;
}

void JoystickExperimentalPlugin::setTooltip(const QString &s)
{
    Q_UNUSED(s);
}

bool JoystickExperimentalPlugin::start()
{
    if(_form == nullptr)
    {
        _form = new Form(); // this form rather side-effect
        _model = new JoystickModel(this);
        _joy->connect(_joy, SIGNAL(onAxePitch(float)), _model, SLOT(setJOYSTICK_PITCH(float)));
        _joy->connect(_joy, SIGNAL(onAxeRoll(float)), _model, SLOT(setJOYSTICK_ROLL(float)));
        _joy->connect(_joy, SIGNAL(onAxeYaw(float)), _model, SLOT(setJOYSTICK_YAW(float)));
        _joy->connect(_joy, SIGNAL(onThrottleAxe(float)), _model, SLOT(setJOYSTICK_THROTTLE(float)));
        _joy->connect(_joy, SIGNAL(onJoystickButtons(uint)), _model, SLOT(setJOYSTICK_BUTTONS(uint)));
        _joy->start();
    }
    return true;
}

void JoystickExperimentalPlugin::stop()
{

}
// UNUSED
void JoystickExperimentalPlugin::updateValue(OVPluginParam *param, QVariant newValue)
{
    Q_UNUSED(param);
    Q_UNUSED(newValue);
}
// UNUSED
void JoystickExperimentalPlugin::sendValue(OVPluginParam *param, QVariant value)
{
    Q_UNUSED(param);
    Q_UNUSED(value);
}

void JoystickExperimentalPlugin::setRollAxe(float value)
{
    sendParam(_joystickRoll, value);
}

void JoystickExperimentalPlugin::setPitchAxe(float value)
{
    sendParam(_joystickPitch, value);
}

void JoystickExperimentalPlugin::setYawAxe(float value)
{
    sendParam(_joystickYaw, value);
}

void JoystickExperimentalPlugin::setThrottleAxe(float value)
{
    sendParam(_joystickThrottle, value);
}

void JoystickExperimentalPlugin::setJoystickButtons(unsigned value)
{
    sendParam(_joystickButtons, value);
}

JoystickExperimentalPlugin::~JoystickExperimentalPlugin()
{
    delete _model;
    delete _joy;
    delete _form;
}
OVP(JoystickExperimentalPlugin)
