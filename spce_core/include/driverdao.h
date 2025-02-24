#ifndef DRIVERDAO_H
#define DRIVERDAO_H

#include <dao.h>
#include "driver.h"
#include "spce_core_global.h"

class QSqlDatabase;

namespace spce_core {
class SPCE_CORE_EXPORT DriverDao : public Dao<Driver>
{
public:
    DriverDao(QSqlDatabase &database);


    // Dao interface
public:
    void init() const;
    Driver get(int id) const;
    void add(Driver &record) const;
    QVector<Driver> getAll() const;
};
} // namespace spce_core


#endif // DRIVERDAO_H
