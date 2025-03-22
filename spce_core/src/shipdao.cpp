#include "shipdao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "ship.h"

namespace spce_core {
ShipDao::ShipDao(QSqlDatabase &database)
    : Dao<Ship>(database)
{

}

void ShipDao::init() const
{
    if (!mDatabase.tables().contains("spce_ship"))
    {
        QSqlQuery query(mDatabase);
        QString queryString = R"(
        CREATE TABLE spce_ship(
        id       INTEGER,
        imo      TEXT UNIQUE,
        tonnage  INTEGER,
        name     TEXT,
        flag     TEXT,
        flag_url TEXT,
        callsign TEXT,
        type     TEXT,
        year     INTEGER,
        PRIMARY KEY(id AUTOINCREMENT)
        ))";

        if (!query.exec(queryString))
        {
            qDebug() << "Could not create table " + query.lastError().text();
        }
    }

}

void ShipDao::add(Ship &ship) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO spce_ship(imo, tonnage, name, flag, flag_url, callsign, type, year)
        VALUES(:imo, :tonnage, :name, :flag, :flag_url, :callsign, :type, :year)
    )");
    query.bindValue(":imo", ship.imo());
    query.bindValue(":tonnage", ship.tonnage());
    query.bindValue(":name", ship.name());
    query.bindValue(":flag", ship.flag());
    query.bindValue(":flag_url", ship.flagUrl());
    query.bindValue(":callsign", ship.callSign());
    query.bindValue(":type", ship.type());
    query.bindValue(":year", ship.year());

    if (!query.exec())
    {
        qDebug() << "Could not add ship to the database " + query.lastError().text();
        return;
    }

    ship.setId(query.lastInsertId().toInt());
}

Ship ShipDao::get(int id) const
{
    Ship ship;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM spce_ship
        WHERE id = :id
    )");

    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Could not get ship from db. " << query.lastError().text();
        return ship;
    }

    if (query.next())
    {
        ship.setId(query.value("id").toInt());
        ship.setImo(query.value("imo").toString());
        ship.setCallSign(query.value("callsign").toString());
        ship.setFlag(query.value("flag").toString());
        ship.setFlagUrl(query.value("flag_url").toString());
        ship.setTonnage(query.value("tonnage").toInt());
        ship.setType(query.value("type").toString());
        ship.setYear(query.value("year").toInt());
        ship.setName(query.value("name").toString());

    }

    return ship;
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
        ship.setId(query.value("id").toInt());
        ship.setImo(imo);
        ship.setCallSign(query.value("callsign").toString());
        ship.setFlag(query.value("flag").toString());
        ship.setFlagUrl(query.value("flag_url").toString());
        ship.setTonnage(query.value("tonnage").toInt());
        ship.setType(query.value("type").toString());
        ship.setYear(query.value("year").toInt());
        ship.setName(query.value("name").toString());

    }

    return ship;
}

QVector<Ship> ShipDao::getAll() const
{
    QVector<Ship> ships;
    QSqlQuery query(mDatabase);

    if (query.exec("SELECT * FROM spce_ship"))
    {
        while (query.next())
        {
            ships.append(Ship(
                query.value("imo").toString(),
                query.value("tonnage").toInt(),
                query.value("name").toString(),
                query.value("flag").toString(),
                query.value("flag_url").toString(),
                query.value("callsign").toString(),
                query.value("type").toString(),
                query.value("id").toInt()
                ));
        }
    }

    else
    {
        qDebug() << "Could not get ships from db. " << query.lastError().text();
    }

    return ships;
}

} // namespace spce_core



void spce_core::ShipDao::update(const Ship &record) const
{
}

QVector<spce_core::Ship> spce_core::ShipDao::getShips(const QString &name) const
{
    QVector<Ship> ships;
    QSqlQuery query(mDatabase);
    query.prepare(R"(SELECT * FROM spce_ship WHERE name LIKE :name)");
    query.bindValue(":name", "%" + name + "%");
    qDebug() << "Query string : " << query.lastQuery();

    if (query.exec())
    {

        while (query.next())
        {
            ships.append(Ship(
                query.value("imo").toString(),
                query.value("tonnage").toInt(),
                query.value("name").toString(),
                query.value("flag").toString(),
                query.value("flag_url").toString(),
                query.value("callsign").toString(),
                query.value("type").toString(),
                query.value("id").toInt()
                ));
        }
    }
    else
    {
        qDebug() << "Could not get ships like " << name << " from db. " << query.lastError().text();
        qDebug() << "Query string : " << query.lastQuery();
    }

    return ships;
}
