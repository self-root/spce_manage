#ifndef DRIVER_H
#define DRIVER_H

#include <QString>

#include "baseentity.h"

#include "spce_core_global.h"

namespace spce_core {
class SPCE_CORE_EXPORT Driver : public BaseEntity
{
public:
    Driver(int id = -1);
    Driver(const QString &name, int id = -1);

    QString nom() const;
    void setName(const QString &newName);

private:
    QString mName;
};
} // namespace spce_core


#endif // DRIVER_H
