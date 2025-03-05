#include "vehicledao.h"
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace spce_core {
VehicleDao::VehicleDao(QSqlDatabase &database)
    : Dao(database)
{

}

void VehicleDao::init() const
{
    if (mDatabase.tables().contains("vehicle"))
        return;
    QSqlQuery query(mDatabase);
    QString queryString = R"(
        CREATE TABLE vehicle(
            id     INTEGER,
            type   TEXT,
            number TEXT,
            PRIMARY KEY(id AUTOINCREMENT)
        )
    )";

    if (!query.exec(queryString))
        qWarning() << "Unable to create vehicle table: " << query.lastError().text();
}

Vehicle VehicleDao::get(int id) const
{
    Vehicle vehicle;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM vehicle
        WHERE id = :id
    )");

    query.bindValue(":id", id);

    if (query.exec())
    {
        if (query.next())
        {
            vehicle = Vehicle(
                query.value("type").toString(),
                query.value("number").toString(),
                query.value("id").typeId()
            );
        }
    }
    else
    {
        qWarning() << "Could not get vehicl from the database: " << query.lastError().text();
    }
    return vehicle;
}

void VehicleDao::add(Vehicle &record) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSETRT INTO vehicle(type, number)
        VALUES(:type, :number)
    )");

    query.bindValue(":type", record.type());
    query.bindValue(":number", record.number());

    if (query.exec())
        record.setId(query.lastInsertId().toInt());
    else
        qWarning() << "Could not insert vehicle: " << record.number() << " to the db: " << query.lastError().text();
}

QVector<Vehicle> VehicleDao::getAll() const
{
    QVector<Vehicle> vehicles;

    QSqlQuery query(mDatabase);
    if (query.exec("SELECT * FROM vehicle"))
    {
        while (query.next())
        {
            vehicles.append(Vehicle(
                query.value("type").toString(),
                query.value("number").toString(),
                query.value("id").toInt()
            ));
        }
    }
    else
        qWarning() << "Could not get vehicles fro the db: " << query.lastError().text();

    return vehicles;
}
} // namespace spce_core




void spce_core::VehicleDao::update(const Vehicle &record) const
{
}
