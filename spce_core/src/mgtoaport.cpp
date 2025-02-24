#include "mgtoaport.h"
#include <QSettings>
#include <QStringList>

namespace spce_core {
MGTOAPort::MGTOAPort()
{

}

void MGTOAPort::readPortSettings()
{
    QSettings settings;
    settings.beginGroup("port");
    mPortName = settings.value("name", "Toamasina Port").toString();
    mTerminals = settings.value("terminals", QStringList()).toStringList();
    settings.endGroup();
}

void MGTOAPort::addTerminal(const QString &terminal)
{
    if (!mTerminals.contains(terminal))
    {
        mTerminals.append(terminal);
        saveTerminalSettings();
    }
}

QString MGTOAPort::portName() const
{
    return mPortName;
}

void MGTOAPort::setPortName(const QString &newPortName)
{
    mPortName = newPortName;
    QSettings settings;
    settings.setValue("port/name", mPortName);
}

QStringList MGTOAPort::terminals() const
{
    return mTerminals;
}

void MGTOAPort::setTerminals(const QStringList &newTerminals)
{
    mTerminals = newTerminals;
}

void MGTOAPort::saveTerminalSettings()
{
    QSettings settings;
    settings.beginGroup("port");
    settings.setValue("terminals", mTerminals);
    settings.endGroup();
}
} // namespace spce_core

