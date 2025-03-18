#include "mgtoaport.h"
#include <QSettings>
#include <QStringList>

namespace spce_core {

QString MGTOAPort::portName()
{
    QSettings settings;
    settings.beginGroup("port");
    QString portName = settings.value("name", "Toamasina Port").toString();
    settings.endGroup();

    return portName;
}

void MGTOAPort::setPortName(const QString &newPortName)
{
    QSettings settings;
    settings.setValue("port/name", newPortName);
}

QStringList MGTOAPort::terminals()
{
    QSettings settings;
    settings.beginGroup("port");
    QStringList terminals_ = settings.value("terminals", QStringList()).toStringList();
    settings.endGroup();

    return terminals_;
}

void MGTOAPort::setTerminals(const QStringList &newTerminals)
{
    QSettings settings;
    settings.beginGroup("port");
    settings.setValue("terminals", newTerminals);
    settings.endGroup();
}

} // namespace spce_core

