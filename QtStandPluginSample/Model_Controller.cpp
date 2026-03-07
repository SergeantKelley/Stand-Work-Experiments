#include "Model_Controller.h"

SampleModel::SampleModel(Controller * controller, QObject *parent) : QObject(parent),
    _controller(controller)
{

}

int SampleModel::PARAMETER_IN() const
{
    return _PARAMETER_IN;
}

int SampleModel::PARAMETER_OUT() const
{
   return _PARAMETER_OUT;
}

void SampleModel::setPARAMETER_IN(int PARAMETER_IN)
{
    if (_PARAMETER_IN == PARAMETER_IN) return;
    _PARAMETER_IN = PARAMETER_IN;
    _controller->sendingParam(_PARAMETER_IN); // requesting controller class to make possible special actions first and then sending
    emit PARAMETER_INChanged(PARAMETER_IN);
}

void SampleModel::setPARAMETER_OUT(int PARAMETER_OUT)
{
    if (_PARAMETER_OUT == PARAMETER_OUT) return;
    _PARAMETER_OUT = PARAMETER_OUT;
    _controller->processLabel(_PARAMETER_OUT); // requesting controller class to proccess incoming data and set some text for label
    emit PARAMETER_OUTChanged(PARAMETER_OUT);
}

/* The controller implementation starts here */

Controller::Controller(StandPluginSample* plugin, Form *form): _form(form),
    _plugin(plugin)
{

}

// some tricky operations method
void Controller::processLabel(int value)
{
    _form->getLabel()->setText("Hello from experiment - " + QString::number(value));
}

// You can perform some actions before sending data
void Controller::sendingParam(int value)
{
    _plugin->send(value);
}
