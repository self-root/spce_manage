#include "eliminateurdao.h"
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace spce_core {
EliminateurDao::EliminateurDao(QSqlDatabase &database)
    : Dao(database)

{}

void EliminateurDao::init() const
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
                responsable TEXT,

                PRIMARY KEY(id AUTOINCREMENT)
            )
        )");

        if (!created)
        {
            qWarning() << "Could not create eliminateur table: " << query.lastError().text();
        }
    }
}

void EliminateurDao::add(Eliminateur &record) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO eliminateur(nom, address, tel, email, receptionSite, responsable)
        VALUES(:nom, :address, :tel, :email, :receptionSite, :responsable)
    )");

    query.bindValue(":nom", record.nom());
    query.bindValue(":address", record.address());
    query.bindValue(":tel", record.tel());
    query.bindValue(":email", record.email());
    query.bindValue(":receptionSite", record.receptionSite());
    query.bindValue(":responsable", record.responsabble());

    if (query.exec())
    {
        record.setId(query.lastInsertId().toInt());
    }
    else
        qWarning() << "Error while inserting eliminateur into database: " << query.lastError().text();
}

Eliminateur EliminateurDao::get(int id) const
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
                query.value("responsable").toString(),
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

Eliminateur EliminateurDao::get(const QString &name) const
{
    Eliminateur eliminateur;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM eliminateur
        WHERE nom = :nom
    )");

    query.bindValue(":nom", name);

    if (query.exec())
    {
        if (query.next())
        {
            eliminateur = Eliminateur(
                query.value("nom").toString(),
                query.value("address").toString(),
                query.value("tel").toString(),
                query.value("email").toString(),
                query.value("responsable").toString(),
                query.value("receptionSite").toString(),
                query.value("id").toInt()
            );
            qDebug() << "ElimID: " << eliminateur.id();
        }
    }

    else
    {
        qWarning() << "Error while reading eliminateur " << name << " from db: " << query.lastError().text();
    }

    return eliminateur;
}

QVector<Eliminateur> EliminateurDao::getAll() const
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
                query.value("responsable").toString(),
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



void spce_core::EliminateurDao::update(const Eliminateur &record) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        UPDATE eliminateur
        SET nom = :nom, address = :address, tel = :tel , email = :email, responsable = :responsable, receptionSite = :receptionSite
        WHERE id = :id
    )");

    query.bindValue(":nom", record.nom());
    query.bindValue(":address", record.address());
    query.bindValue(":tel", record.tel());
    query.bindValue(":email", record.email());
    query.bindValue(":responsable", record.responsabble());
    query.bindValue(":receptionSite", record.receptionSite());
    query.bindValue(":id", record.id());

    if (query.exec())
    {

    }
    else
        qWarning() << "Error while updating eliminateur into database: " << query.lastError().text();
}
