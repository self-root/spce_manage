#include "bsddao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>

namespace spce_core {
BSDDao::BSDDao(QSqlDatabase &database)
    : Dao(database)
{

}
void BSDDao::init() const
{
    if (mDatabase.tables().contains("bsd"))
        return;

    QSqlQuery query(mDatabase);
    QString queryString = R"(
        CREATE TABLE bsd(
            id        INTEGER,
            date      TEXT,
            f_comm    INTEGER,
            f_coll    INTEGER,
            f_elim    INTEGER,
            f_ship    INTEGER,
            f_driver  INTEGER,
            f_vehicle INTEGER,
            f_invoice INTEGER,

            PRIMARY KEY(id AUTOINCREMENT),
            FOREIGN KEY(f_comm) REFERENCES commissionnaire(id) ON DELETE CASCADE,
            FOREIGN KEY(f_coll) REFERENCES collectionnaire(id) ON DELETE CASCADE,
            FOREIGN KEY(f_elim) REFERENCES eliminateur(id) ON DELETE CASCADE,
            FOREIGN KEY(f_ship) REFERENCES ship(id) ON DELETE CASCADE,
            FOREIGN KEY(f_driver) REFERENCES driver(id) ON DELETE CASCADE,
            FOREIGN KEY(f_vehicle) REFERENCES vehicle(id) ON DELETE CASCADE,
            FOREIGN KEY(f_invoice) REFERENCES invoice(id) ON DELETE CASCADE
        )
    )";

    if (!query.exec(queryString))
        qWarning() << "Could not create table bsd: " << query.lastError().text();
}

BSD BSDDao::get(int id) const
{
    BSD bsd;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM bsd
        WHERE id = :id
    )");

    query.bindValue(":id", id);

    if (query.exec())
    {
        if (query.next())
        {
            bsd = BSD(
                Commissionnaire(query.value("f_comm").toInt()),
                Collecteur(query.value("f_coll").toInt()),
                Eliminateur(query.value("f_elim").toInt()),
                Driver(query.value("f_driver").toInt()),
                Vehicle(query.value("f_vehicle").toInt()),
                Ship(query.value("f_ship").toInt()),
                QDate::fromString(query.value("date").toString(), "dd-MM-yyyy"),
                query.value("f_invoice").toInt(),
                query.value("id").toInt()
            );
        }
    }

    else
        qWarning() << "Could not get BSD from db: " << query.lastError().text();

    return bsd;
}

void BSDDao::add(BSD &record) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO bsd(f_comm, f_coll, f_elim, f_driver, f_vehicle, f_ship, date, f_invoice)
        VALUES (:f_comm, :f_coll, :f_elim, :f_driver, :f_vehicle, :f_ship, :date, :f_invoice)
    )");

    query.bindValue(":f_comm", record.commissionnaire().id());
    query.bindValue(":f_coll", record.collecteur().id());
    query.bindValue(":f_elim", record.eliminateur().id());
    query.bindValue(":f_driver", record.driver().id());
    query.bindValue(":f_vehicle", record.vehicle().id());
    query.bindValue(":f_ship", record.ship().id());
    query.bindValue(":date", record.date().toString("dd-MM-yyyy"));
    query.bindValue(":f_invoice", record.invoiceId());

    if (query.exec())
        record.setId(query.lastInsertId().toInt());

    else
        qWarning() << "Unable to save BSD: " << query.lastError().text();
}

QVector<BSD> BSDDao::getAll() const
{
    QVector<BSD> bsds;
    QSqlQuery query;

    if (query.exec("SELECT * FROM bsd"))
    {
        while (query.next())
        {
            bsds.append(BSD(
                Commissionnaire(query.value("f_comm").toInt()),
                Collecteur(query.value("f_coll").toInt()),
                Eliminateur(query.value("f_elim").toInt()),
                Driver(query.value("f_driver").toInt()),
                Vehicle(query.value("f_vehicle").toInt()),
                Ship(query.value("f_ship").toInt()),
                QDate::fromString(query.value("date").toString(), "dd-MM-yyyy"),
                query.value("f_invoice").toInt(),
                query.value("id").toInt()
                ));
        }
    }

    else
        qWarning() << "Could not get BSDs fro db: " << query.lastError();

    return bsds;
}
} // namespace spce_core






void spce_core::BSDDao::update(const BSD &record) const
{
}
