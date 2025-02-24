#ifndef MGTOAPORT_H
#define MGTOAPORT_H

#include "spce_core_global.h"
#include <QString>
#include <QStringList>

namespace spce_core {
class SPCE_CORE_EXPORT MGTOAPort
{
public:
    MGTOAPort();
    void readPortSettings();
    void addTerminal(const QString &terminal);
    QString portName() const;
    void setPortName(const QString &newPortName);
    QStringList terminals() const;
    void setTerminals(const QStringList &newTerminals);
    void saveTerminalSettings();

private:
    QString mPortName;
    QStringList mTerminals;

};
} // namespace spce_core


#endif // MGTOAPORT_H
