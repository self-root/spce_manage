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
    void init() const override;
    Vehicle get(int id) const override;
    void add(Vehicle &record) const override;
    QVector<Vehicle> getAll() const override;
    void update(const Vehicle &record) const override;
};
} // namespace spce_core


#endif // VEHICLEDAO_H
