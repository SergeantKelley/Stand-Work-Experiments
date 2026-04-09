#include "Window.h"

using namespace utils;

glm::mat4 scenePerspective, camera; // view and perspective matrixes

// Keyboard Handler
void onKeyboardCallback(GLFWwindow * win, int key, int scancode, int action, int mods)
{
     static float xShift = 0.0f; // just for demo purpouces
     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)   glfwSetWindowShouldClose(win, true);
     if (key == GLFW_KEY_F5 && action == GLFW_PRESS)  Window::Instance().toggleFullscreenMode(win, (Window::Instance().isFullscreen())? false: true);
     // just for demo purposes
     if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
     {
         Window::Instance().pyramid.setPosition(-xShift, 0.0f, 0.0f);
         emit Window::Instance().onLeftButton(xShift);
         xShift += 1.0f;
     }
     if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
     {
         Window::Instance().pyramid.setPosition(-xShift, 0.0f, 0.0f);
         emit Window::Instance().onLeftButton(xShift);
          xShift -= 1.0f;
     }
}
// Mouse Handler
void onMouseCallback(GLFWwindow *win, int button, int action, int mods)
{

}

// Window reshape handler
void onReshapeCallback(GLFWwindow * win, int newWidth, int newHeight)
{
    Window::Instance().setWindowRatio((float)newWidth / (float)newHeight);
    glViewport(0, 0, newWidth, newHeight);
    scenePerspective = glm::perspective(1.0472f, Window::Instance().getWindowRatio(), 0.1f, 1000.0f);
}
// Get single instance of the Window
Window& Window::Instance()
{
    static Window app;
    return app;
}
// glfw3 initialization
Window::Window(QObject *parent): QThread(parent)
{
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
}

Window::~Window()
{
    _windowName = NULL;
}
// Window Size
void Window::setWindowSize(int x, int y)
{
    _sizeX = x;
    _sizeY = y;
    glfwSetWindowSize(_win, _sizeX, _sizeY);
    glViewport(0, 0, _sizeX, _sizeY);
}
// getting all primary information, creating window, setting event handlers
void Window::Init(bool fullscreenMode)
{
    _monitor = glfwGetPrimaryMonitor();
    _mode = glfwGetVideoMode(_monitor);
    _win = glfwCreateWindow((fullscreenMode)? _mode->width :_sizeX, (fullscreenMode)? _mode->height :_sizeY, _windowName,  (fullscreenMode)? _monitor : NULL, NULL);
    _fullscreen = fullscreenMode;
    glfwMakeContextCurrent(_win);
    centerWindow();
    if (glewInit() != GLEW_OK)
    {
        printf("Oh my, failed to initialize GLAD!");
    }
    initRenderingContext(); // setup defalut states
    // setup event handlers
    glfwSetKeyCallback(_win, onKeyboardCallback);
    glfwSetMouseButtonCallback(_win, onMouseCallback);
    glfwSetWindowSizeCallback(_win, onReshapeCallback);
}
// Main window title
void Window::setWindowName(const char* windowName)
{
    _windowName = windowName;
    glfwSetWindowTitle(_win, _windowName);
}
// Vertical syncronization
void Window::enableVertSyncronization(bool vSync)
{
     glfwSwapInterval(vSync ? 1 : 0);
     _vSync = vSync;
}
// Ajusting openGL context
void Window::setWindowContextVersion(int mainor, int major)
{
    _contextMajor = major;
    _contextMinor = mainor;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _contextMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _contextMinor);
}

// Display loop
void Window::Display(GLFWwindow * win, double currTime)
{
    Q_UNUSED(win);
    Q_UNUSED(currTime);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

 // Rendering, uncomment models to render them
    // sphere.Render(camera, scenePerspective);
    // cube.Render(camera, scenePerspective);
    pyramid.Render(camera, scenePerspective);
}
// The main event loop
int Window::exec()
{
    while (!glfwWindowShouldClose(_win))
    {
        Display(_win, glfwGetTime());
        glfwSwapBuffers(_win);
        glfwPollEvents();
    }
    glfwDestroyWindow(_win);
    glfwTerminate();
    return glfwWindowShouldClose(_win);
}
// initial rendering conditions
void Window::initRenderingContext()
{
    GLuint renderingProgram;
    // camera position
    setCameraPosition(0.0f, 0.0f, -20.0f);
    // cooking the shaders
    QString vsPath = "/home/" + qgetenv("USER") + "/.oper_vis/plugins/Shaders/vertShader.glsl";
    QString fsPath = "/home/" + qgetenv("USER") + "/.oper_vis/plugins/Shaders/fragShader.glsl";
    renderingProgram = Shader::createShaderProgram(vsPath.toStdString().c_str(), fsPath.toStdString().c_str());
    // sphere
    sphere.setupVerts();
    sphere.setScale(3.0f);
    sphere.setPosition(10.0f, 0.0f, 0.0f);
    sphere.setShader(renderingProgram);
    // cube
    cube.setupVerts();
    cube.setPosition(-10.0f, 0.0f, 0.0f);
    cube.setScale(2.25f);
    cube.setShader(renderingProgram);
    // pyramid
    pyramid.setupVerts();
    pyramid.setShader(renderingProgram);
    pyramid.setScaleX(2.25f);
    pyramid.setScaleZ(2.25f);
    pyramid.setRotationX(90.0f);
    // precomputing scene perspective and camera
    glfwGetFramebufferSize(_win, &_sizeX, &_sizeY);
    _windowRatio = (float)_sizeX / (float)_sizeY;
    scenePerspective = glm::perspective(1.0472f, _windowRatio, 0.1f, 1000.0f);
    camera = glm::translate(glm::mat4(1.0f), glm::vec3(_cameraX, _cameraX, _cameraZ));
    // setting background color
    glClearColor(0.3f, 0.3f, 0.3f, 1.0);
}
// fullscreen mode
void Window::toggleFullscreenMode(GLFWwindow * win, bool fullscreen)
{
    _mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if(fullscreen) glfwSetWindowMonitor(win, glfwGetPrimaryMonitor(), 0, 0, _mode->width, _mode->height, _mode->refreshRate);
    else
    {
        _winStatus.windowedX = _monitorX + (_mode->width - _sizeX) / 2;
        _winStatus.windowedY = _monitorY + (_mode->height - _sizeY) / 2;
        glfwSetWindowMonitor(win, nullptr, _winStatus.windowedX, _winStatus.windowedY, _winStatus.windowedW, _winStatus.windowedH, 0);
    }
    _fullscreen = fullscreen;
}
// Cursor visibility over the main window
void Window::setMouseCursorVisible(bool visibility)
{
    glfwSetInputMode(_win, GLFW_CURSOR, visibility? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}
// The Main Window Position Centering
void Window::centerWindow()
{
    if (!_mode)
    {
        printf("Oh no, problem getting video mode info!");
        return;
    }
    glfwGetMonitorPos(_monitor, &_monitorX, &_monitorY);
    glfwGetWindowSize(_win, &_sizeX, &_sizeY);
    glfwSetWindowPos(_win, _monitorX + (_mode->width - _sizeX) / 2, _monitorY + (_mode->height - _sizeY) / 2);
}
// Nose Gear Angle Changing
void Window::OnNoseGearAngleChanged(float value)
{
    pyramid.setRotationZ(value);
}
// Thread Entry point
void Window::run()
{
    Window::Instance().Init(false);
    Window::Instance().setWindowName("Hello Window");
    Window::Instance().exec();
}
