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
};
} // namespace spce_core


#endif // INVOICEDAO_H
