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
    void init() const override;
    Driver get(int id) const override;
    Driver get(const QString &name) const;
    void add(Driver &record) const override;
    QVector<Driver> getAll() const override;
    void update(const Driver &record) const override;
};
} // namespace spce_core


#endif // DRIVERDAO_H
