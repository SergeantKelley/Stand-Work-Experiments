#include "NoName.h"


NoName::NoName()
{
    setName("NoName");
    icons.addPixmap(QPixmap(":/icon1"), QIcon::Normal, QIcon::On);
}

QWidget *NoName::getMainWidget()
{
    return _form;
}

void NoName::setTooltip(const QString &s)
{

}

bool NoName::start()
{
    if(_form == nullptr)
    {
        _form = new Form();
    }
    return true;
}

void NoName::stop()
{

}

void NoName::updateValue(OVPluginParam *param, QVariant newValue)
{

}
OVP(NoName)
