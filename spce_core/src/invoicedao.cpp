#include "invoicedao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QSqlRecord>

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
            number    TEXT UNIQUE NOT NULL,
            quantity  FLOAT,
            unitPrice FLOAT,
            amount    FLOAT,
            f_ship    INTEGER,
            item      TEXT NOT NULL,
            i_date    TEXT NOT NULL,

            PRIMARY KEY(id AUTOINCREMENT),
            FOREIGN KEY(f_ship) REFERENCES spce_ship(id) ON DELETE CASCADE
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
                QDate::fromString(query.value("i_date").toString(), "yyyy-MM-dd"),
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
        INSERT INTO invoice(number, quantity, unitPrice, amount, f_ship, item, i_date)
        VALUES (:number, :quantity, :unitPrice, :amount, :f_ship, :item, :date)
    )");

    query.bindValue(":number", record.number());
    query.bindValue(":quantity", record.quantity());
    query.bindValue(":unitPrice", record.unitPrice());
    query.bindValue(":amount", record.amount());
    query.bindValue(":f_ship", record.ship().id());
    query.bindValue(":item", record.item());
    query.bindValue(":date", record.date().toString("yyyy-MM-dd"));

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
            QDate::fromString(query.value("i_date").toString(), "yyyy-MM-dd"),
            query.value("invoice.id").toInt()
            ));
    }

    return invoices;
}

QVector<Invoice> InvoiceDao::getAllWithDateRange(const QDate &start, const QDate &end) const
{
    QVector<Invoice> invoices;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT * FROM invoice
        INNER JOIN spce_ship
        ON spce_ship.id = invoice.f_ship
        INNER JOIN bsd ON invoice.id = bsd.f_invoice
        WHERE i_date BETWEEN :start_date AND :end_date
        ORDER BY invoice.i_date DESC
    )");
    query.bindValue(":start_date", start.toString(Qt::ISODate));
    query.bindValue(":end_date", end.toString(Qt::ISODate));
    if (!query.exec())
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
            QDate::fromString(query.value("i_date").toString(), "yyyy-MM-dd"),
            query.value("invoice.id").toInt()
            ));
    }

    return invoices;
}

void InvoiceDao::update(const Invoice &record) const
{
}

void InvoiceDao::update(const QVariantMap &record) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        UPDATE invoice
        SET quantity = :quantity, amount = :amount
        WHERE number = :number
    )");
    query.bindValue(":quantity", record["quantity"].toDouble());
    query.bindValue(":amount", record["amount"].toDouble());
    query.bindValue(":number", record["invoice_number"].toString());

    if (!query.exec())
    {
        qDebug() << "Failed to update invoice: " << record["invoice_number"].toString() << " error: " << query.lastError();
    }
}

QString InvoiceDao::lastInvoiceNumber() const
{
    QString number = "";
    QSqlQuery query(mDatabase);

    if (query.exec("SELECT id,  number FROM invoice ORDER BY id DESC LIMIT 1"))
    {
        if (query.next())
            number = query.value("number").toString();
    }
    else
        qDebug() << "Unable to get the last invoice number: " << query.lastError();

    return number;
}

QVector<QMap<QString, QVariant> > InvoiceDao::getInvoices(const QDate &start, const QDate &end) const
{
    QVector<QMap<QString, QVariant>> data;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT invoice.number AS invoice_number, quantity, amount, i_date, spce_ship.type as ship_type, spce_ship.name AS ship_name, flag, flag_url, commissionnaire.denomination AS denom
        FROM invoice
        INNER JOIN bsd ON invoice.id = bsd.f_invoice
        INNER JOIN commissionnaire ON commissionnaire.id = bsd.f_comm
        INNER JOIN driver ON driver.id = bsd.f_driver
        INNER JOIN spce_ship ON spce_ship.id = invoice.f_ship
        WHERE i_date BETWEEN :start_date AND :end_date
        ORDER BY invoice.i_date DESC
    )");
    query.bindValue(":start_date", start.toString(Qt::ISODate));
    query.bindValue(":end_date", end.toString(Qt::ISODate));

    if (query.exec())
    {
        while (query.next()) {
            data.push_back(queryToMap(query));
        }
    }

    else
    {
        qWarning() << "Could not get invoices from db : " << query.lastError().text();
    }

    return data;
}

QVector<QPair<QString, int> > InvoiceDao::getShipTypeDistro(const QDate &start, const QDate &end) const
{
    QVector<QPair<QString, int>> distros;
    QSqlQuery query(mDatabase);
    query.prepare(R"(
        SELECT type, count(*) AS count from invoice
        INNER JOIN spce_ship ON spce_ship.id = invoice.f_ship
        WHERE i_date BETWEEN :start_date AND :end_date
        GROUP BY type ORDER BY count DESC;

    )");
    query.bindValue(":start_date", start.toString(Qt::ISODate));
    query.bindValue(":end_date", end.toString(Qt::ISODate));

    if (query.exec())
    {
        while (query.next())
        {
            distros.append(
                {
                    {query.value("type").toString(), query.value("count").toInt()}
                }
            );
        }
    }

    else
        qDebug() << "Could not get ship type distribution from db: " << query.lastError();

    return distros;
}

QMap<QString, QVariant> InvoiceDao::queryToMap(const QSqlQuery &query) const
{
    QMap<QString, QVariant> map;
    QSqlRecord record = query.record();
    for (int i = 0; i < record.count(); i++)
    {
        map[record.fieldName(i)] = query.value(i);
    }
    return map;
}

void InvoiceDao::remove(const QString &invoiceNumber) const
{
    QSqlQuery query(mDatabase);
    query.prepare(R"(DELETE FROM invoice WHERE number = :number)");
    query.bindValue(":number", invoiceNumber);

    if (!query.exec())
        qDebug() << "Could not remove invoice: " << invoiceNumber << " from db: " << query.lastError();
}

} // namespace spce_core


