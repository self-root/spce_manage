#ifndef SHIPDAO_H
#define SHIPDAO_H

#include "spce_core_global.h"

class QSqlDatabase;
namespace spce_core {

class Ship;

class SPCE_CORE_EXPORT ShipDao
{
public:
    ShipDao(QSqlDatabase &database);
    void init() const;
    void addShip(Ship &ship);
    Ship getShip(const QString &imo);
private:
    QSqlDatabase &mDatabase;
};

} // namespace spce_core

#endif // SHIPDAO_H
