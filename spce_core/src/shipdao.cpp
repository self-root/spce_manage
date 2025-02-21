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
        year INTEGER,
        PRIMARY KEY(id AUTOINCREMENT)
        ))";

        if (!query.exec(queryString))
        {
            qDebug() << "Could not create table " + query.lastError().text();
        }
    }

}

void ShipDao::addShip(Ship &ship) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO spce_ship(imo, tonnage, name, flag, flag_url, callsign, type, year)
        VALUES(:imo, :tonnage, :name, :flag, :flag_url, :callsign, :type, :year)
    )");
    query.bindValue(":imo", ship.imo);
    query.bindValue(":tonnage", ship.tonnage);
    query.bindValue(":name", ship.name);
    query.bindValue(":flag", ship.flag);
    query.bindValue(":flag_url", ship.flagUrl);
    query.bindValue(":callsign", ship.callSign);
    query.bindValue(":type", ship.type);
    query.bindValue(":year", ship.year);

    if (!query.exec())
    {
        qDebug() << "Could not add ship to the database " + query.lastError().text();
        return;
    }

    ship.id = query.lastInsertId().toInt();
}

Ship ShipDao::getShip(const QString &imo) const
{
    Ship ship;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM spce_ship
        WHERE imo = :imo
    )");

    query.bindValue(":imo", imo);

    if (!query.exec())
    {
        qDebug() << "Could not get ship from db. " << query.lastError().text();
        return ship;
    }

    if (query.next())
    {
        ship.id = query.value("id").toInt();
        ship.imo = imo;
        ship.callSign = query.value("callsign").toString();
        ship.flag = query.value("flag").toString();
        ship.flagUrl = query.value("flag_url").toString();
        ship.tonnage = query.value("tonnage").toInt();
        ship.type = query.value("type").toString();
        ship.year = query.value("year").toInt();
        ship.name = query.value("name").toString();

    }

    return ship;
}

} // namespace spce_core

