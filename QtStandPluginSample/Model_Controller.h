#ifndef MODEL_CONTROLLER_H
#define MODEL_CONTROLLER_H

#include <QObject>
#include <QMessageBox>

#include "StandPluginSample.h"
#include "form.h"

class StandPluginSample; // forward declaration

/*
 * Controller class handles all complex actions or data manipulations
 * Just in case Q_OBJECT macro and QObject inheritance was included
 */
class Controller : public QObject
{
     Q_OBJECT

public:
    explicit Controller(StandPluginSample* plugin, Form * form);

public:
    void processLabel(int value);
    void sendingParam(int value);

private:
    Form * _form = nullptr;
    StandPluginSample * _plugin = nullptr;

private:
};

/*
 * Model class is a class for storing an application logic and it's states
 * All data passes through model class in both directions
 */
class SampleModel : public QObject
{
    Q_OBJECT

public:
    explicit SampleModel(Controller * controller, QObject *parent = 0);
// props
public:
    Q_PROPERTY(int PARAMETER_IN READ PARAMETER_IN WRITE setPARAMETER_IN NOTIFY PARAMETER_INChanged)
    Q_PROPERTY(int PARAMETER_OUT READ PARAMETER_OUT WRITE setPARAMETER_OUT NOTIFY PARAMETER_OUTChanged)

public:
    int PARAMETER_IN() const;
    int PARAMETER_OUT() const;

private:
    Controller * _controller    = nullptr;
    int _PARAMETER_IN           = 0;
    int _PARAMETER_OUT          = 0;

signals:
    void PARAMETER_INChanged(int PARAMETER_IN);
    void PARAMETER_OUTChanged(int PARAMETER_OUT);

public slots:
    void setPARAMETER_IN(int PARAMETER_IN);
    void setPARAMETER_OUT(int PARAMETER_OUT);

};

#endif // SAMPLEMODEL_H
