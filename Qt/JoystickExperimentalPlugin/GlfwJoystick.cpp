#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GlfwJoystick.h"

#define _USE_MATH_DEFINES

GlutJoystick::GlutJoystick(QObject *parent) : QThread(parent)
{

}
// joystick poll interval equals 50 ms
void GlutJoystick::JoystickTimerCallback(int jID)
{
    int axesCount = 0;
    int buttonCount = 0;
    // getting status
    const unsigned char* buttons = glfwGetJoystickButtons(jID, &buttonCount);
    const float* axes = glfwGetJoystickAxes(jID, &axesCount);
    // To prevent plugin crash when joy is unconnected. if joy exists, transfer it's data to his model. Do nothing otherwise
    if(jID != -1)
    {
        emit onAxeRoll(axes[0]);
        emit onAxePitch(axes[2]);
        emit onAxeYaw(axes[1]);
        emit onThrottleAxe(axes[3]);
        emit onJoystickButtons((unsigned)(buttons[11] << 16) | (unsigned)(buttons[1] << 8) | buttons[0]);
    }
}
// Becuase the OpenGL window context wasn't created, it doesn't work here
void Joystick_Callback(int joy_id, int event)
{
    if (event == GLFW_CONNECTED) QMessageBox::information(0, "info","Joy connected");
    if (event == GLFW_DISCONNECTED) QMessageBox::information(0, "info","Joy Disconnected");
}
// left unused, just for debugging or printing joy information out when using standalone app format
static void getJoystickInfo(int jID)
{
    int axesCount = 0;
    int buttonCount = 0;
    const char* joyName = glfwGetJoystickName(jID);
    const float* axes = glfwGetJoystickAxes(jID, &axesCount);
    const unsigned char* buttons = glfwGetJoystickButtons(jID, &buttonCount);

    printf("\r[%s] Axes: ", joyName ? joyName : "Joystick unknown :-(");
    for (int axe = 0; axe < axesCount; axe++)
    {
        printf("%d = %.2f", axe, axes[axe]);
    }
    printf("| Buttons: ");
    for (int button = 0; button < buttonCount; button++)
    {
        printf("%d = %d", button, buttons[button]? 1 : 0);
    }
    fflush(stdout);
}
// Main Entry Point
void GlutJoystick::run()
{
        if (not glfwInit())
        {
            exit(EXIT_FAILURE);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwSetTime(0.0); // set start time value
        float lastTime = glfwGetTime();
        for (int joystick = GLFW_JOYSTICK_1; joystick <= GLFW_JOYSTICK_LAST; joystick++)
        { // enumeration
            if (glfwJoystickPresent(joystick))
            {
                jID = joystick; // joy was found, setup ID and break the cycle
                break;
            }
        }
        glfwSetJoystickCallback(Joystick_Callback);
        while (true)
        {
           float currentTime = glfwGetTime();
           if (currentTime - lastTime >= dt) JoystickTimerCallback(jID); // dt time is up, calling timer tick func
           glfwPollEvents();
        }
        // shutdown
        glfwTerminate();
        exit(EXIT_SUCCESS);
}
