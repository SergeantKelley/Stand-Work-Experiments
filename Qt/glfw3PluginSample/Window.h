#ifndef WINDOW_H
#define WINDOW_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QMessageBox>
#include <QByteArray>
#include <QCoreApplication>

#include <stack>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Sphere.h"
#include "Cube.h"
#include "Pyramid.h"

#include "Shader.h"


// window default settings
struct WindowStatus
{
    int windowedX = 150; // position X
    int windowedY = 150; // position Y
    int windowedW = 800; // size X
    int windowedH = 600; // size Y
};


/*
*   The Window class provides window events handling,
*
*/
class Window : public QThread
{
    Q_OBJECT
public:
    Window(QObject *parent = 0);
    ~Window();
    static Window& Instance();

public: // test-objects
    Pyramid pyramid;
    Cube cube;
    Sphere sphere;

public:
    void setWindowSize(int x, int y);
    void Init(bool fullscreenMode);
    void setWindowName(const char* windowName);
    void enableVertSyncronization(bool vSync);
    void setWindowContextVersion(int mainor, int major);
    int exec();
    void toggleFullscreenMode(GLFWwindow * win, bool fullscreen);
    inline bool isFullscreen() { return _fullscreen; }
    void setMouseCursorVisible(bool visibility);                    // mouse visibility over the window
    inline float getWindowRatio() {return _windowRatio; }
    inline void setWindowRatio(float ratio) { _windowRatio = ratio; }
    inline void setCameraPosition(float x, float y, float z) { _cameraX = x;  _cameraY = y; _cameraZ = z;}

private:
    void Display(GLFWwindow * win, double currTime);    // display loop function
    void initRenderingContext();                        // setup initial render settings or states
    void centerWindow();                                // set the main window centered

private:
    GLFWwindow * _win           = nullptr;  // GLFW window instance
    const char * _windowName    = "Unnamed Window"; // window title
    bool _vSync                 = false;    // vertical screen sync
    bool _fullscreen            = false;    // fullscree mode
    int _contextMajor           = 3;        // openGL context
    int _contextMinor           = 3;        // openGL context
    int _sizeX                  = 800;      // window size X
    int _sizeY                  = 600;      // window size Y
    int _monitorX               = 0;        // monitor size X
    int _monitorY               = 0;        // monitor size Y
    float _windowRatio;                     // w / h window ratio
    WindowStatus _winStatus;                // base window info (size and upper left corner position)
    const GLFWvidmode * _mode   = nullptr;  // video mode info
    GLFWmonitor * _monitor      = nullptr;  // monitor info
    glm::mat4 _pMat;                        // perspective matrix
    float _cameraX = 0.0f;                  // camera position
    float _cameraY = 0.0f;                  // camera position
    float _cameraZ = 0.0f;                  // camera position

signals:
    void onLeftButton(float value);         // for demo purposes
    void onRightButton(float value);        // for demo purposes

public slots:
    void OnNoseGearAngleChanged(float value); //

    // QThread interface
protected:
    virtual void run() override;
};
#endif // WINDOW_H

