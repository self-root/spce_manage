#include "eliminateurdao.h"
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace spce_core {
EliminateurDao::EliminateurDao(QSqlDatabase &database)
    : mDatabase(database)

{}

void EliminateurDao::init()
{
    if (!mDatabase.tables().contains("eliminateur"))
    {
        QSqlQuery query(mDatabase);
        bool created = query.exec(R"(
            CREATE TABLE eliminateur(
                id INTEGER,
                nom TEXT,
                address TEXT,
                tel TEXT,
                email TEXT,
                receptionSite TEXT,

                PRIMARY KEY(id AUTOINCREMENT)
            )
        )");

        if (!created)
        {
            qWarning() << "Could not create eliminateur table: " << query.lastError().text();
        }
    }
}

void EliminateurDao::addEliminateur(Eliminateur &eliminateur)
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO eliminateur(nom, address, tel, email, receptionSite)
        VALUES(:nom, :address, :tel, :email, :receptionSite)
    )");

    query.bindValue(":nom", eliminateur.nom());
    query.bindValue(":address", eliminateur.address());
    query.bindValue(":tel", eliminateur.tel());
    query.bindValue(":email", eliminateur.email());
    query.bindValue(":receptionSite", eliminateur.receptionSite());

    if (query.exec())
    {
        eliminateur.setId(query.lastInsertId().toInt());
    }
    else
        qWarning() << "Error while inserting eliminateur into database: " << query.lastError().text();
}

Eliminateur EliminateurDao::getEliminateur(int id)
{
    Eliminateur eliminateur;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM eliminateur
        WHERE id = :id
    )");

    query.bindValue(":id", id);

    if (query.exec())
    {
        if (query.next())
        {
            eliminateur = Eliminateur(
                query.value("nom").toString(),
                query.value("address").toString(),
                query.value("tel").toString(),
                query.value("email").toString(),
                query.value("receptionSite").toString(),
                id
                );
        }
    }

    else
    {
        qWarning() << "Error while reading eliminateur " << id << " from db: " << query.lastError().text();
    }

    return eliminateur;
}

Eliminateur EliminateurDao::getEliminateur(const QString &name)
{
    Eliminateur eliminateur;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM eliminateur
        WHERE nom = :nom
    )");

    query.bindValue(":name", name);

    if (query.exec())
    {
        if (query.next())
        {
            eliminateur = Eliminateur(
                query.value("nom").toString(),
                query.value("address").toString(),
                query.value("tel").toString(),
                query.value("email").toString(),
                query.value("receptionSite").toString(),
                query.value("id").toInt()
                );
        }
    }

    else
    {
        qWarning() << "Error while reading eliminateur " << name << " from db: " << query.lastError().text();
    }

    return eliminateur;
}

QVector<Eliminateur> EliminateurDao::getEliminateurs()
{
    QSqlQuery query(mDatabase);
    QVector<Eliminateur> eliminateurs;
    if (query.exec("SELECT * FROM eliminateur"))
    {
        while (query.next())
        {
            eliminateurs.append(Eliminateur(
                query.value("nom").toString(),
                query.value("address").toString(),
                query.value("tel").toString(),
                query.value("email").toString(),
                query.value("receptionSite").toString(),
                query.value("id").toInt()
                ));
        }
    }

    else {
        qWarning() << "Error while getting commissionnaires from the db: " << query.lastError();
    }

    return eliminateurs;
}
} // namespace spce_core

