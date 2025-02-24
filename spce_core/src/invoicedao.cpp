#include "invoicedao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>

namespace spce_core {
InvoiceDao::InvoiceDao(QSqlDatabase &database)
    : Dao(database)
{

}

void InvoiceDao::init() const
{
    if (mDatabase.tables().contains("invoice"))
        return;

    QSqlQuery query(mDatabase);
    QString queryString = R"(
        CREATE TABLE invoice(
            id        INTEGER,
            number    TEXT UNIQUE,
            quantity  FLOAT,
            unitPrice FLOAT,
            amount    FLOAT,
            f_ship    INTEGER,
            item      TEXT,

            PRIMARY KEY(id AUTOINCREMENT),
            FOREIGN KEY(f_ship) REFERENCES spce_ship(id)
        )
    )";

    if (!query.exec(queryString))
        qWarning() << "Unable to create invoice table: " << query.lastError().text();

}

Invoice InvoiceDao::get(int id) const
{
    Invoice invoice;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM invoice
        INNER JOIN spce_ship
        ON spce_ship.id = invoice.f_ship
        WHERE invoice.id = :id
    )");

    query.bindValue(":id", id);

    if (query.exec())
    {
        if (query.next())
        {
            Ship ship;
            ship.setId(query.value("spce_ship.id").toInt());
            ship.setImo(query.value("imo").toString());
            ship.setName(query.value("name").toString());

            invoice = Invoice(
                query.value("number").toString(),
                query.value("quantity").toDouble(),
                query.value("unitPrice").toDouble(),
                query.value("amount").toDouble(),
                ship,
                query.value("item").toString(),
                query.value("invoice.id").toInt()
            );
        }
    }
    else
    {
        qWarning() << "Could not get invoice from db : " << query.lastError().text();
    }

    return invoice;
}

void InvoiceDao::add(Invoice &record) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        INSERT INTO invoice(number, quantity, unitPrice, amount, f_ship, item)
        VALUES (:number, :quantity, :unitPrice, :amount, :f_ship, :item)
    )");

    query.bindValue(":number", record.number());
    query.bindValue(":quantity", record.quantity());
    query.bindValue(":unitPrice", record.unitPrice());
    query.bindValue(":amount", record.amount());
    query.bindValue(":f_ship", record.ship().id());
    query.bindValue(":item", record.item());

    if (query.exec())
        record.setId(query.lastInsertId().toInt());

    else
        qWarning() << "Could not add invoice into the database: " << query.lastError().text();
}

QVector<Invoice> InvoiceDao::getAll() const
{
    QVector<Invoice> invoices;
    QSqlQuery query(mDatabase);
    QString queryString = R"(
        SELECT * FROM invoice
        INNER JOIN spce_ship
        ON spce_ship.id = invoice.f_ship
    )";

    if (!query.exec(queryString))
        qWarning() << "Unable to read invoices from db: " << query.lastError().text();

    while (query.next())
    {
        Ship ship;
        ship.setId(query.value("spce_ship.id").toInt());
        ship.setImo(query.value("imo").toString());
        ship.setName(query.value("name").toString());

        invoices.append(Invoice(
            query.value("number").toString(),
            query.value("quantity").toDouble(),
            query.value("unitPrice").toDouble(),
            query.value("amount").toDouble(),
            ship,
            query.value("item").toString(),
            query.value("invoice.id").toInt()
            ));
    }

    return invoices;
}
} // namespace spce_core




