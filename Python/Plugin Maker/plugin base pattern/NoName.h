#ifndef NONAME_H
#define NONAME_H

#include <QObject>
#include "oper_vis_plugin.h"
#include "form.h"

class NoName: public OVPlugin
{

public:
    NoName();

    // OVPlugin interface
public:
    virtual QWidget *getMainWidget() override;
    virtual void setTooltip(const QString &s) override;
    virtual bool start() override;
    virtual void stop() override;
    virtual void updateValue(OVPluginParam *param, QVariant newValue) override;

private:
    Form * _form = nullptr;

signals:

};

#endif // NO_NAME
