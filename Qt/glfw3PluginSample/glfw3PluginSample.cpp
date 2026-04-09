#include "glfw3PluginSample.h"


glfw3PluginSample::glfw3PluginSample()
{
    setName("glfw3PluginSample");
    icons.addPixmap(QPixmap(":/icon1"), QIcon::Normal, QIcon::On);
    _greenParam = makeParam("main", "MAKE_GREEN_COLOR");
    _ngAngle = makeParam("main", "NG_ANGLE");
    _Xcoord = makeParam("main", "NG_X_3D");
}
// clean up resorces
glfw3PluginSample::~glfw3PluginSample()
{
    delete _model;
    delete _controller;
}
// returning the base qt form widget
QWidget *glfw3PluginSample::getMainWidget()
{
    return _form;
}

void glfw3PluginSample::setTooltip(const QString &s)
{
    Q_UNUSED(s);
}
// plugin initialization
bool glfw3PluginSample::start()
{
    if(_form == nullptr)
    {
        _form = new Form();
        _controller = new Controller(this, _form);
        _model = new Model(_controller);
        Window::Instance().connect(_model, SIGNAL(NOSE_GEAR_ANGLEChanged(float)), &Window::Instance(), SLOT(OnNoseGearAngleChanged(float)));
        Window::Instance().connect(&Window::Instance(), SIGNAL(onLeftButton(float)), _model, SLOT(setX_COORD_3D(float)));
        Window::Instance().start();
    }
    return true;
}

void glfw3PluginSample::stop()
{

}
// refreshing model data incoming from an experiment context
void glfw3PluginSample::updateValue(OVPluginParam *param, QVariant newValue)
{
       if(_model == nullptr) return; // To prevent plugin crashing at the very start
       if(param == _ngAngle) _model->setProperty("NOSE_GEAR_ANGLE", newValue);
}
// left here for demo: sending X coordinate from a 3D scene to an experiment
void glfw3PluginSample::setPositionX(float X)
{
      sendParam(_Xcoord, X);
}

OVP(glfw3PluginSample)
