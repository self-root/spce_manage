#ifndef ELIMINATEURDAO_H
#define ELIMINATEURDAO_H
#include "spce_core_global.h"
#include "eliminateur.h"

class QSqlDatabase;

namespace spce_core {
class SPCE_CORE_EXPORT EliminateurDao
{
public:
    EliminateurDao(QSqlDatabase &database);
    void init();
    void addEliminateur(Eliminateur &eliminateur);
    Eliminateur getEliminateur(int id);
    Eliminateur getEliminateur(const QString &name);
    QVector<Eliminateur> getEliminateurs();

private:
    QSqlDatabase &mDatabase;
};
} // namespace spce_core


#endif // ELIMINATEURDAO_H
