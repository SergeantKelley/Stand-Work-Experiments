#include "Model_Controller.h"

Model::Model(Controller * controller, QObject *parent) : QObject(parent), _controller(controller)
{

}

float Model::NOSE_GEAR_ANGLE() const
{
    return _NOSE_GEAR_ANGLE;
}

float Model::X_COORD_3D() const
{
    return _X_COORD_3D;
}
// input data
void Model::setNOSE_GEAR_ANGLE(float NOSE_GEAR_ANGLE)
{
    {
        if (_NOSE_GEAR_ANGLE == NOSE_GEAR_ANGLE) return;
        _NOSE_GEAR_ANGLE = NOSE_GEAR_ANGLE;
        emit NOSE_GEAR_ANGLEChanged(NOSE_GEAR_ANGLE);
    }
}
// output data
void Model::setX_COORD_3D(float X_COORD_3D)
{
        if (_X_COORD_3D == X_COORD_3D) return;
        _X_COORD_3D = X_COORD_3D;
        _controller->sendingParam(_X_COORD_3D); // requesting controller class to make possible special actions first and then sending
        emit X_COORD_3DChanged(X_COORD_3D);
}

Controller::Controller(glfw3PluginSample *plugin, Form *form): _form(form),
_plugin(plugin)
{

}

void Controller::processData(float value)
{
    Q_UNUSED(value);
}
// sending data to an experiment
void Controller::sendingParam(float value)
{
    _plugin->setPositionX(value);
}
