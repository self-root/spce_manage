#include "commissionnairedao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace spce_core {
CommissionnaireDao::CommissionnaireDao(QSqlDatabase &database)
    : Dao<Commissionnaire>(database){}

void CommissionnaireDao::init() const
{
    if (!mDatabase.tables().contains("commissionnaire"))
    {
        QSqlQuery query(mDatabase);
        bool created = query.exec(R"(
            CREATE TABLE commissionnaire(
                id           INTEGER,
                denomination TEXT,
                address      TEXT,
                tel          TEXT,
                email        TEXT,
                responsable  TEXT,

                PRIMARY KEY(id AUTOINCREMENT)
            )
        )");

        if (!created)
        {
            qWarning() << "Could not create commissionnaire table: " << query.lastError().text();
        }
    }
}

void CommissionnaireDao::add(Commissionnaire &commissionnaire) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO commissionnaire(denomination, address, tel, email, responsable)
        VALUES(:denomination, :address, :tel, :email, :responsable)
    )");

    query.bindValue(":denomination", commissionnaire.nom());
    query.bindValue(":address", commissionnaire.address());
    query.bindValue(":tel", commissionnaire.tel());
    query.bindValue(":email", commissionnaire.email());
    query.bindValue(":responsable", commissionnaire.responsabble());

    if (query.exec())
    {
        commissionnaire.setId(query.lastInsertId().toInt());
    }
    else
        qWarning() << "Error while inserting commissionnaire into database: " << query.lastError().text();
}

Commissionnaire CommissionnaireDao::get(int id) const
{
    Commissionnaire commissionnaire;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM commissionnaire
        WHERE id = :id
    )");

    query.bindValue(":id", id);

    if (query.exec())
    {
        if (query.next())
        {
            commissionnaire = Commissionnaire(
                query.value("denomination").toString(),
                query.value("address").toString(),
                query.value("tel").toString(),
                query.value("email").toString(),
                query.value("responsable").toString(),
                id
                );
        }
    }

    else
    {
        qWarning() << "Error while reading commissionnaire " << id << " from db: " << query.lastError().text();
    }

    return commissionnaire;
}

Commissionnaire CommissionnaireDao::get(const QString &denomination) const
{
    Commissionnaire commissionnaire;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM commissionnaire
        WHERE denomination = :denomination
    )");

    query.bindValue(":denomination", denomination);

    if (query.exec())
    {
        if (query.next())
        {
            commissionnaire = Commissionnaire(
                denomination,
                query.value("address").toString(),
                query.value("tel").toString(),
                query.value("email").toString(),
                query.value("responsable").toString(),
                query.value("id").toInt()
                );
        }
    }

    else
    {
        qWarning() << "Error while reading commissionnaire " << denomination << " from db: " << query.lastError().text();
    }

    return commissionnaire;
}

QVector<Commissionnaire> CommissionnaireDao::getAll() const
{
    QSqlQuery query(mDatabase);
    QVector<Commissionnaire> commissionnaires;
    if (query.exec("SELECT * FROM commissionnaire"))
    {
        while (query.next())
        {
            commissionnaires.append(Commissionnaire(
                query.value("denomination").toString(),
                query.value("address").toString(),
                query.value("tel").toString(),
                query.value("email").toString(),
                query.value("responsable").toString(),
                query.value("id").toInt()
            ));
        }
    }

    else {
        qWarning() << "Error while getting commissionnaires from the db: " << query.lastError();
    }

    return commissionnaires;
}
} // namespace spce_core

