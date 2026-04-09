#ifndef MODEL_CONTROLLER_H
#define MODEL_CONTROLLER_H

#include <QObject>
#include <QMessageBox>

#include "glfw3PluginSample.h"
#include "form.h"


class glfw3PluginSample; // forward declaration

/*
 * Controller class handles all complex actions or data manipulations
 * Just in case Q_OBJECT macro and QObject inheritance was included
 */
class Controller : public QObject
{
     Q_OBJECT

public:
    explicit Controller(glfw3PluginSample* plugin, Form * form);

public:
    void processData(float value);
    void sendingParam(float value);

private:
    glfw3PluginSample * _plugin = nullptr;
    Form* _form = nullptr;
};


/*
 * Model class is a class for storing an application logic and it's states
 * All data passes through model class in both directions
 */
class Model : public QObject
{
    Q_OBJECT

public:
    explicit Model(Controller * controller, QObject *parent = 0);

public:
    Q_PROPERTY(float NOSE_GEAR_ANGLE READ NOSE_GEAR_ANGLE WRITE setNOSE_GEAR_ANGLE NOTIFY NOSE_GEAR_ANGLEChanged)
    Q_PROPERTY(float X_COORD_3D READ X_COORD_3D WRITE setX_COORD_3D NOTIFY X_COORD_3DChanged)

public:
    float NOSE_GEAR_ANGLE() const;
    float X_COORD_3D() const;

private:
    float _NOSE_GEAR_ANGLE;
    float _X_COORD_3D;
    Controller * _controller    = nullptr;

signals:
    void NOSE_GEAR_ANGLEChanged(float NOSE_GEAR_ANGLE);
    void X_COORD_3DChanged(float X_COORD_3D);

public slots:
    void setNOSE_GEAR_ANGLE(float NOSE_GEAR_ANGLE);
    void setX_COORD_3D(float X_COORD_3D);
};

#endif // MODEL_H
