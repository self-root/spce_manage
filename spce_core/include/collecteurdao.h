#ifndef COLLECTEURDAO_H
#define COLLECTEURDAO_H

#include "spce_core_global.h"
#include "collecteur.h"
#include "dao.h"

class QSqlDatabase;

namespace spce_core {
class SPCE_CORE_EXPORT CollecteurDao : public Dao<Collecteur>
{
public:
    CollecteurDao(QSqlDatabase &database);
    void init() const override;
    void add(Collecteur &collecteur) const override;
    Collecteur get(int id) const override;
    Collecteur get(const QString &name) const;
    QVector<Collecteur> getAll() const override;
    void update(const Collecteur &record) const override;
};
} // namespace spce_core


#endif // COLLECTEURDAO_H
