#include "collecteurdao.h"
#include <QSqlDatabase>
#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>

namespace spce_core {

CollecteurDao::CollecteurDao(QSqlDatabase &database)
    : Dao<Collecteur>(database)
{

}

void CollecteurDao::init() const
{
    if (!mDatabase.tables().contains("collecteur"))
    {
        QSqlQuery query(mDatabase);
        bool created = query.exec(R"(
            CREATE TABLE collecteur(
                id          INTEGER,
                nom         TEXT,
                address     TEXT,
                tel         TEXT,
                email       TEXT,
                responsable TEXT,

                PRIMARY KEY(id AUTOINCREMENT)
            )
        )");

        if (!created)
        {
            qWarning() << "Could not create collecteur table: " << query.lastError().text();
        }
    }
}

void CollecteurDao::add(Collecteur &collecteur) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO collecteur(nom, address, tel, email, responsable)
        VALUES(:nom, :address, :tel, :email, :responsable)
    )");

    query.bindValue(":nom", collecteur.nom());
    query.bindValue(":address", collecteur.address());
    query.bindValue(":tel", collecteur.tel());
    query.bindValue(":email", collecteur.email());
    query.bindValue(":responsable", collecteur.responsabble());

    if (query.exec())
    {
        collecteur.setId(query.lastInsertId().toInt());
    }
    else
        qWarning() << "Error while inserting collecteur into database: " << query.lastError().text();
}

Collecteur CollecteurDao::get(int id) const
{
    Collecteur collecteur;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM collecteur
        WHERE id = :id
    )");

    query.bindValue(":id", id);

    if (query.exec())
    {
        if (query.next())
        {
            collecteur = Collecteur(
                query.value("nom").toString(),
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
        qWarning() << "Error while reading collecteur " << id << " from db: " << query.lastError().text();
    }

    return collecteur;
}

Collecteur CollecteurDao::get(const QString &name) const
{
    Collecteur collecteur;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM collecteur
        WHERE nom = :nom
    )");

    query.bindValue(":nom", name);

    if (query.exec())
    {
        if (query.next())
        {
            collecteur = Collecteur(
                query.value("nom").toString(),
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
        qWarning() << "Error while reading collecteur " << name << " from db: " << query.lastError().text();
    }

    return collecteur;
}

QVector<Collecteur> CollecteurDao::getAll() const
{
    QSqlQuery query(mDatabase);
    QVector<Collecteur> collecteurs;
    if (query.exec("SELECT * FROM collecteur ORDER BY id DESC"))
    {
        while (query.next())
        {
            collecteurs.append(Collecteur(
                query.value("nom").toString(),
                query.value("address").toString(),
                query.value("tel").toString(),
                query.value("email").toString(),
                query.value("responsable").toString(),
                query.value("id").toInt()
                ));
        }
    }

    else {
        qWarning() << "Error while getting collecteur from the db: " << query.lastError();
    }

    return collecteurs;
}

void CollecteurDao::update(const Collecteur &record) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        UPDATE collecteur
        SET nom = :nom, address = :address, tel = :tel , email = :email, responsable = :responsable
        WHERE id = :id
    )");

    query.bindValue(":nom", record.nom());
    query.bindValue(":address", record.address());
    query.bindValue(":tel", record.tel());
    query.bindValue(":email", record.email());
    query.bindValue(":responsable", record.responsabble());
    query.bindValue(":id", record.id());

    if (query.exec())
    {

    }
    else
        qWarning() << "Error while updating collecteur into database: " << query.lastError().text();
}

} // namespace spce_core

