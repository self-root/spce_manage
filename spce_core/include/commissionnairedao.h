#ifndef COMMISSIONNAIREDAO_H
#define COMMISSIONNAIREDAO_H

#include "spce_core_global.h"
#include "dao.h"
#include "commissionnaire.h"
#include <QVector>

class QSqlDatabase;

namespace spce_core {

class SPCE_CORE_EXPORT CommissionnaireDao : public Dao<Commissionnaire>
{
public:
    CommissionnaireDao(QSqlDatabase &database);

    void init() const override;
    void add(Commissionnaire &commissionnaire) const override;
    Commissionnaire get(int id) const override;
    Commissionnaire get(const QString &denomination) const;
    QVector<Commissionnaire> getAll() const override;

};
} // namespace spce_core



#endif // COMMISSIONNAIREDAO_H
