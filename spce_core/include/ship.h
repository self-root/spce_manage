#ifndef SHIP_H
#define SHIP_H

#include "spce_core_global.h"
#include <QString>

namespace spce_core {
class SPCE_CORE_EXPORT Ship
{
public:
    Ship();
    int id = -1;
    QString imo;
    int tonnage;
    QString name;
    QString flag;
    QString flagUrl;
    QString callSign;
    QString type;
};

} // namespace spce_core

#endif // SHIP_H
