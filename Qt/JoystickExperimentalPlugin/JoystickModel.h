#ifndef JOYSTICKMODEL_H
#define JOYSTICKMODEL_H

#include <QObject>
#include <QMessageBox>
#include "JoystickExperimentalPlugin.h"

class JoystickExperimentalPlugin;

class JoystickModel : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(float JOYSTICK_YAW READ JOYSTICK_YAW WRITE setJOYSTICK_YAW NOTIFY JOYSTICK_YAWChanged)
    Q_PROPERTY(float JOYSTICK_PITCH READ JOYSTICK_PITCH WRITE setJOYSTICK_PITCH NOTIFY JOYSTICK_PITCHChanged)
    Q_PROPERTY(float JOYSTICK_ROLL READ JOYSTICK_ROLL WRITE setJOYSTICK_ROLL NOTIFY JOYSTICK_ROLLChanged)
    Q_PROPERTY(unsigned JOYSTICK_NWS READ JOYSTICK_NWS WRITE setJOYSTICK_NWS NOTIFY JOYSTICK_NWSChanged)
    Q_PROPERTY(float JOYSTICK_THROTTLE READ JOYSTICK_THROTTLE WRITE setJOYSTICK_THROTTLE NOTIFY JOYSTICK_THROTTLEChanged)
    Q_PROPERTY(unsigned JOYSTICK_BUTTONS READ JOYSTICK_BUTTONS WRITE setJOYSTICK_BUTTONS NOTIFY JOYSTICK_BUTTONSChanged)

public:
    explicit JoystickModel(JoystickExperimentalPlugin * plugin, QObject *parent = 0);
    float JOYSTICK_YAW() const;
    float JOYSTICK_PITCH() const;
    float JOYSTICK_ROLL() const;
    unsigned JOYSTICK_NWS() const;
    float JOYSTICK_THROTTLE() const;    
    unsigned JOYSTICK_BUTTONS() const;

signals:
    void JOYSTICK_YAWChanged(float JOYSTICK_YAW);
    void JOYSTICK_PITCHChanged(float JOYSTICK_PITCH);
    void JOYSTICK_ROLLChanged(float JOYSTICK_ROLL);
    void JOYSTICK_NWSChanged(unsigned JOYSTICK_NWS);    
    void JOYSTICK_THROTTLEChanged(float JOYSTICK_THROTTLE);    
    void JOYSTICK_BUTTONSChanged(unsigned JOYSTICK_BUTTONS);

public slots:
    void setJOYSTICK_YAW(float JOYSTICK_YAW);
    void setJOYSTICK_PITCH(float JOYSTICK_PITCH);
    void setJOYSTICK_ROLL(float JOYSTICK_ROLL);
    void setJOYSTICK_NWS(unsigned JOYSTICK_NWS);
    void setJOYSTICK_THROTTLE(float JOYSTICK_THROTTLE);
    void setJOYSTICK_BUTTONS(unsigned JOYSTICK_BUTTONS);

private:
    float _JOYSTICK_YAW;
    float _JOYSTICK_PITCH;
    float _JOYSTICK_ROLL;
    unsigned _JOYSTICK_NWS;
    JoystickExperimentalPlugin * _plugin = nullptr;
    float _JOYSTICK_THROTTLE;
    unsigned _JOYSTICK_BUTTONS;
};

#endif // JOYSTICKMODEL_H
