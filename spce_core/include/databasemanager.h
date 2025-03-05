#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "spce_core_global.h"
#include <QString>

#include "shipdao.h"
#include "commissionnairedao.h"
#include "collecteurdao.h"
#include "eliminateurdao.h"
#include "driverdao.h"
#include "vehicledao.h"
#include "invoicedao.h"
#include "bsddao.h"

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
    const CommissionnaireDao mCommissionnaireDao;
    const CollecteurDao mCollecteurDao;
    const EliminateurDao mEliminateurDao;
    const DriverDao mDriverDao;
    const VehicleDao mVehicleDao;
    const InvoiceDao mInvoiceDao;
    const BSDDao mBSDDao;

    template <typename T>
    const Dao<T> &getDao();

};



} // namespace spce

#endif // DATABASEMANAGER_H
