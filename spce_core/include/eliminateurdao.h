#ifndef ELIMINATEURDAO_H
#define ELIMINATEURDAO_H
#include "spce_core_global.h"
#include "eliminateur.h"
#include "dao.h"

class QSqlDatabase;

namespace spce_core {
class SPCE_CORE_EXPORT EliminateurDao : public Dao<Eliminateur>
{
public:
    EliminateurDao(QSqlDatabase &database);
    void init() const override;
    void add(Eliminateur &redord) const override;
    Eliminateur get(int id) const override;
    Eliminateur get(const QString &name) const;
    QVector<Eliminateur> getAll() const override;
    void update(const Eliminateur &record) const override;
};
} // namespace spce_core


#endif // ELIMINATEURDAO_H
