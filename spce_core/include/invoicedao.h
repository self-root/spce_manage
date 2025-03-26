#ifndef INVOICEDAO_H
#define INVOICEDAO_H

#include <dao.h>
#include "spce_core_global.h"
#include "invoice.h"

class QSqlDatabase;

class QSqlQuery;

namespace spce_core {
class SPCE_CORE_EXPORT InvoiceDao : public Dao<Invoice>
{
public:
    InvoiceDao(QSqlDatabase &database);

    // Dao interface
public:
    void init() const override;
    Invoice get(int id) const override;
    void add(Invoice &record) const override;
    QVector<Invoice> getAll() const override;
    QVector<Invoice> getAllWithDateRange(const QDate &start, const QDate &end) const;
    void update(const Invoice &record) const override;
    void update(const QVariantMap &record) const;
    QString lastInvoiceNumber() const;
    QVector<QMap<QString, QVariant>> getInvoices(const QDate &start, const QDate &end) const;
    QVector<QPair<QString, int>> getShipTypeDistro(const QDate &start, const QDate &end) const;
    QMap<QString, QVariant> queryToMap(const QSqlQuery &query) const;
    void remove(const QString & invoiceNumber) const;
};
} // namespace spce_core


#endif // INVOICEDAO_H
