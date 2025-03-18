#ifndef MGTOAPORT_H
#define MGTOAPORT_H

#include "spce_core_global.h"
#include <QString>
#include <QStringList>

namespace spce_core {
class SPCE_CORE_EXPORT MGTOAPort
{
public:
    static QString portName();
    static void setPortName(const QString &newPortName);
    static QStringList terminals();
    static void setTerminals(const QStringList &newTerminals);


};
} // namespace spce_core


#endif // MGTOAPORT_H
