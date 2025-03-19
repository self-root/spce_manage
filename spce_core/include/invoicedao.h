#ifndef INVOICEDAO_H
#define INVOICEDAO_H

#include <dao.h>
#include "spce_core_global.h"
#include "invoice.h"

class QSqlDatabase;

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
    void update(const Invoice &record) const override;
    QString lastInvoiceNumber() const;
};
} // namespace spce_core


#endif // INVOICEDAO_H
