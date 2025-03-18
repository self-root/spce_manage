#include "driverdao.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace spce_core {
DriverDao::DriverDao(QSqlDatabase &database)
    : Dao(database)
{}

void DriverDao::init() const
{
    if (mDatabase.tables().contains("driver"))
        return;

    QSqlQuery query(mDatabase);
    const QString queryString = R"(
        CREATE TABLE driver(
            id   INTEGER,
            name TEXT,
            PRIMARY KEY(id AUTOINCREMENT)
        )
    )";
    if (!query.exec(queryString))
        qWarning() << "Failed to create database 'driver'" << query.lastError().text();
}

Driver DriverDao::get(int id) const
{
    Driver driver;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM driver
        WHERE id = :id
    )");

    query.bindValue(":id", id);

    if (!query.exec())
        qWarning() << "Database reading error, DriverDao, get by ID " << id;

    if (query.next())
    {
        driver = Driver(
            query.value("name").toString(),
            query.value("id").toInt()
        );
    }

    return driver;
}

void DriverDao::add(Driver &record) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO drive(name) VALUES(:name)
    )");

    query.bindValue(":name", record.nom());

    if (query.exec())
        record.setId(query.lastInsertId().toInt());
    else
        qWarning() << "Insersion error, Driver " << record.nom() << " : " << query.lastError().text();
}

QVector<Driver> DriverDao::getAll() const
{
    QVector<Driver> drivers;

    QSqlQuery query(mDatabase);

    if (!query.exec("SELECT * FROM driver"))
        qWarning() << "Could not get all drivers from db: " << query.lastError().text();

    while (query.next())
    {
        drivers.append(Driver(query.value("name").toString(), query.value("id").toInt()));
    }

    return drivers;
}
} // namespace spce_core






void spce_core::DriverDao::update(const Driver &record) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        UPDATE driver
        SET name = :name
        WHERE id = :id
    )");

    query.bindValue(":name", record.nom());
    query.bindValue(":id", record.id());

    if (query.exec())
        qDebug() << "Record updated";
    else
        qWarning() << "Update error, Driver " << record.nom() << " : " << query.lastError().text();
}
