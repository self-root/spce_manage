#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "spce_core_global.h"
#include <QString>

#include "shipdao.h"

class QSqlDatabase;

namespace spce_core {

class SPCE_CORE_EXPORT DatabaseManager
{
protected:
    DatabaseManager();
private:
    QSqlDatabase *mDatabase = nullptr;
    static DatabaseManager *_instance;
public:
    static DatabaseManager *instance();
    static void init();
    static QString databasePath();
    const ShipDao mShipDao;

};

#endif // DATABASEMANAGER_H
} // namespace spce

