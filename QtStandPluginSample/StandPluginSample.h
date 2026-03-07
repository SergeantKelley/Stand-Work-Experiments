#ifndef STANDPLUGINSAMPLE_H
#define STANDPLUGINSAMPLE_H

#include <QObject>
#include <QMessageBox>

#include "oper_vis_plugin.h"
#include "form.h"
#include "Model_Controller.h"


class SampleModel;
class Controller;

class StandPluginSample: public OVPlugin
{

public:
    StandPluginSample();
    ~StandPluginSample();

    // OVPlugin interface
public:
    virtual QWidget *getMainWidget() override;
    virtual void setTooltip(const QString &s) override;
    virtual bool start() override;
    virtual void stop() override;
    virtual void updateValue(OVPluginParam *param, QVariant newValue) override;

public:
    void send(int value);

private:
    Form * _form = nullptr;
    
private:
    OVPluginParam * _parameterIn = nullptr;
    OVPluginParam * _parameterOut = nullptr;
    SampleModel * _model = nullptr;
    Controller * _controller = nullptr;

signals:

};

#endif // NO_NAME
