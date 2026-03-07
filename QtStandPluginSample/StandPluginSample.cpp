#include "StandPluginSample.h"

// setup two special parameters
StandPluginSample::StandPluginSample()
{
    setName("StandPluginSample");
    icons.addPixmap(QPixmap(":/icon1"), QIcon::Normal, QIcon::On);
    _parameterIn = makeParam("main","PARAM_STAND_IN");
    _parameterOut = makeParam("main","PARAM_STAND_OUT");

}
// free resources
StandPluginSample::~StandPluginSample()
{
    delete _model;
    delete _controller;
}

// getting main widget
QWidget *StandPluginSample::getMainWidget()
{
    return _form;
}

void StandPluginSample::setTooltip(const QString &s)
{
    // currently unused func. There is nothing to do
}

// Entry point, initializing all things...
bool StandPluginSample::start()
{
    if(_form == nullptr)
    {
        _form = new Form();
        _controller = new Controller(this, _form);
        _model = new SampleModel(_controller);
        _form->connect(_form, SIGNAL(OnSendingSignal(int)), _model, SLOT(setPARAMETER_IN(int)));
    }
    return true;
}

// an additional quit callback function
void StandPluginSample::stop()
{
    // currently unused func. There is nothing to do
}

// updatings for incoming vars
void StandPluginSample::updateValue(OVPluginParam *param, QVariant newValue)
{
    if (param == _parameterOut) _model->setProperty("PARAMETER_OUT", newValue);
}

void StandPluginSample::send(int value)
{
    sendParam(_parameterIn, value); // sending the param to an extperiment real-time context
}
OVP(StandPluginSample)
