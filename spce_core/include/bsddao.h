#ifndef BSDDAO_H
#define BSDDAO_H

#include <dao.h>
#include "spce_core_global.h"

#include "bsd.h"

class QSqlDatabase;

namespace spce_core {
class SPCE_CORE_EXPORT BSDDao : public Dao<BSD>
{
public:
    BSDDao(QSqlDatabase &database);

    // Dao interface
public:
    void init() const override;
    BSD get(int id) const override;
    void add(BSD &record) const override;
    QVector<BSD> getAll() const override;
};
} // namespace spce_core



#endif // BSDDAO_H
