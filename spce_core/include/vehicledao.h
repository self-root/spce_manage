#ifndef VEHICLEDAO_H
#define VEHICLEDAO_H

#include <dao.h>
#include "vehicle.h"
#include "spce_core_global.h"

class QSqlDatabase;

namespace spce_core {
class SPCE_CORE_EXPORT VehicleDao : public Dao<Vehicle>
{
public:
    VehicleDao(QSqlDatabase &database);

    // Dao interface
public:
    void init() const;
    Vehicle get(int id) const;
    void add(Vehicle &record) const;
    QVector<Vehicle> getAll() const;
};
} // namespace spce_core


#endif // VEHICLEDAO_H
