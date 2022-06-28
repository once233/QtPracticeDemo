#include "instance.h"
#include <QDebug>
Q_GLOBAL_STATIC(Instance, cinstance)
Instance::Instance(QObject *parent) : QObject{ parent }
{
}

Instance *Instance::instance()
{
    return cinstance();
}

void Instance::ouputText()
{
    qDebug() << "instance";
}
