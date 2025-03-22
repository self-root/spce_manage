#ifndef SHIPDAO_H
#define SHIPDAO_H

#include "spce_core_global.h"
#include "dao.h"

class QSqlDatabase;
namespace spce_core {

class Ship;

class SPCE_CORE_EXPORT ShipDao : public Dao<Ship>
{
public:
    ShipDao(QSqlDatabase &database);
    void init() const override;
    void add(Ship &ship) const override;
    Ship get(int id) const override;
    Ship getShip(const QString &imo) const;
    QVector<Ship> getAll() const override;
    void update(const Ship &record) const override;
    QVector<Ship> getShips(const QString &name) const;
};

} // namespace spce_core

#endif // SHIPDAO_H
