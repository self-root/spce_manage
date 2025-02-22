#ifndef COMMISSIONNAIREDAO_H
#define COMMISSIONNAIREDAO_H

#include "spce_core_global.h"
#include <QVector>

class QSqlDatabase;

namespace spce_core {
class Commissionnaire;

class SPCE_CORE_EXPORT CommissionnaireDao
{
public:
    CommissionnaireDao(QSqlDatabase &database);

    void init() const;
    void addCommissionaire(Commissionnaire &commissionnaire) const;
    Commissionnaire getCommissionnaire(int id) const;
    Commissionnaire getCommissionnaire(const QString &denomination) const;
    QVector<Commissionnaire> collecteurs() const;

private:
    QSqlDatabase &mDatabase;
};
} // namespace spce_core



#endif // COMMISSIONNAIREDAO_H
