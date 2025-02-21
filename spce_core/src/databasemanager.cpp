#include "databasemanager.h"

#include <QDebug>
#include <QStandardPaths>
#include <QDir>

#include <QSqlDatabase>
#include <QSqlError>
#include <QtLogging>

namespace spce_core {
DatabaseManager *DatabaseManager::_instance = nullptr;

DatabaseManager::DatabaseManager()
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    mShipDao(ShipDao(*mDatabase))
{
    mDatabase->setDatabaseName(DatabaseManager::databasePath());
    qDebug() << "Database path: " << DatabaseManager::databasePath();
    if (!mDatabase->open())
    {
        QString msg = "QSqlDatabase::open: database not open at: " + databasePath() + "\n" + mDatabase->lastError().text();
        qCritical( "%s", msg.toStdString().c_str());
    }

    else {
        mShipDao.init();
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
} // namespace spce


