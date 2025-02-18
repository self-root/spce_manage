#include "shipdao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "ship.h"

namespace spce_core {
ShipDao::ShipDao(QSqlDatabase &database)
    : mDatabase(database)
{

}

void ShipDao::init() const
{
    if (!mDatabase.tables().contains("spce_ship"))
    {
        QSqlQuery query(mDatabase);
        QString queryString = R"(
        CREATE TABLE spce_ship(
        id  INTEGER,
        imo TEXT UNIQUE,
        tonnage INTEGER,
        name TEXT,
        flag TEXT,
        flag_url TEXT,
        callsign TEXT,
        type TEXT,
        PRIMARY KEY(id AUTOINCREMENT)
        ))";

        if (!query.exec(queryString))
        {
            qDebug() << "Could not create table " + query.lastError().text();
        }
    }

}

void ShipDao::addShip(Ship &ship)
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO spce_ship(imo, tonnage, name, flag, flag_url, callsign, type)
        VALUES(:imo, :tonnage, :name, :flag, :flag_url, :callsign, :type)
    )");
    query.bindValue(":imo", ship.imo);
    query.bindValue(":tonnage", ship.tonnage);
    query.bindValue(":name", ship.name);
    query.bindValue(":flag", ship.flag);
    query.bindValue(":flag_url", ship.flagUrl);
    query.bindValue(":callsign", ship.callSign);
    query.bindValue(":type", ship.type);

    if (!query.exec())
    {
        qDebug() << "Could not add ship to the database " + query.lastError().text();
        return;
    }

    ship.id = query.lastInsertId().toInt();
}

Ship ShipDao::getShip(const QString &imo)
{

}

} // namespace spce_core

