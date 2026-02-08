#ifndef GLFWJOYSTICK_H
#define GLFWJOYSTICK_H

#include <QObject>
#include <QThread>
#include <QMessageBox>
#include <iostream>

using namespace std;

class GlutJoystick : public QThread
{
    Q_OBJECT
public:
    explicit GlutJoystick(QObject *parent = 0);

signals:
    void onAxeYaw(float value);
    void onAxePitch(float value);
    void onAxeRoll(float value);
    void onThrottleAxe(float value);
    void onJoystickButtons(unsigned value);

public slots:

    // QThread interface
protected:
    virtual void run() override;

private:
    void JoystickTimerCallback(int jID);

private:
    int jID = -1;           // Joystick ID
    const float dt = 0.05;  // delta time 50ms (joystick polling)

};

#endif // GLFWJOYSTICK_H
