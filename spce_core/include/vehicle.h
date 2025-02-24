#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>

#include <baseentity.h>
#include "spce_core_global.h"

namespace spce_core {
class SPCE_CORE_EXPORT Vehicle : public BaseEntity
{
public:
    Vehicle(int id = -1);
    Vehicle(const QString &type, const QString &number, int id = -1);
    QString type() const;
    void setType(const QString &newType);
    QString number() const;
    void setNumber(const QString &newNumber);

private:
    QString mType;
    QString mNumber;
};
} // namespace spce_core


#endif // VEHICLE_H
