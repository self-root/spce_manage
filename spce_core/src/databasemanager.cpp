#include "databasemanager.h"

#include <QDebug>
#include <QStandardPaths>
#include <QDir>

#include <QSqlDatabase>
#include <QSqlError>
#include <QtLogging>
#include <QSqlQuery>

namespace spce_core {
DatabaseManager *DatabaseManager::_instance = nullptr;

DatabaseManager::DatabaseManager()
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
      mShipDao(ShipDao(*mDatabase)),
        mCommissionnaireDao(CommissionnaireDao(*mDatabase)),
        mCollecteurDao(CollecteurDao(*mDatabase)),
        mEliminateurDao(EliminateurDao(*mDatabase)),
        mDriverDao(DriverDao(*mDatabase)),
        mVehicleDao(VehicleDao(*mDatabase)),
        mInvoiceDao(InvoiceDao(*mDatabase)),
        mBSDDao(BSDDao(*mDatabase))
{
    mDatabase->setDatabaseName(DatabaseManager::databasePath());
    qDebug() << "Database path: " << DatabaseManager::databasePath();
    if (!mDatabase->open())
    {
        QString msg = "QSqlDatabase::open: database not open at: " + databasePath() + "\n" + mDatabase->lastError().text();
        qCritical( "%s", msg.toStdString().c_str());
    }

    else {
        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");
        qDebug() << "Foreign key support enabled!";
        mShipDao.init();
        mCommissionnaireDao.init();
        mCollecteurDao.init();
        mEliminateurDao.init();
        mDriverDao.init();
        mVehicleDao.init();
        mInvoiceDao.init();
        mBSDDao.init();
    }
}

DatabaseManager *DatabaseManager::instance()
{
    if (_instance == nullptr)
        _instance = new DatabaseManager();

    return _instance;
}

void DatabaseManager::init()
{
    qDebug() << "Init database!";
}

QString DatabaseManager::databasePath()
{
    QStringList locations = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    QString appDataLocation = locations.first();
    QDir app_dir(appDataLocation);
    if (!app_dir.exists())
        app_dir.mkpath(appDataLocation);
    QString path = QDir::cleanPath(appDataLocation + QDir::separator() + QString("spce_data.db"));
    return path;
}

template<>
const Dao<Ship> &DatabaseManager::getDao<Ship>()
{
    return mShipDao;
}

template<>
const Dao<Commissionnaire> &DatabaseManager::getDao<Commissionnaire>()
{
    return mCommissionnaireDao;
}

template<>
const Dao<Collecteur> &DatabaseManager::getDao<Collecteur>()
{
    return mCollecteurDao;
}

template<>
const Dao<Driver> &DatabaseManager::getDao<Driver>()
{
    return mDriverDao;
}

template<>
const Dao<Vehicle> &DatabaseManager::getDao<Vehicle>()
{
    return mVehicleDao;
}

template<>
const Dao<Eliminateur> &DatabaseManager::getDao<Eliminateur>()
{
    return mEliminateurDao;
}

template<>
const Dao<BSD> &DatabaseManager::getDao<BSD>()
{
    return mBSDDao;
}

} // namespace spce


