#ifndef COLLECTEURDAO_H
#define COLLECTEURDAO_H

#include "spce_core_global.h"
#include "collecteur.h"

class QSqlDatabase;

namespace spce_core {
class SPCE_CORE_EXPORT CollecteurDao
{
public:
    CollecteurDao(QSqlDatabase &database);
    void init() const;
    void addCollecteur(Collecteur &collecteur);
    Collecteur getCollecteur(int id);
    Collecteur getCollecteur(const QString &name);
    QVector<Collecteur> getCollecteurs();
private:
    QSqlDatabase &mDatabase;
};
} // namespace spce_core


#endif // COLLECTEURDAO_H
