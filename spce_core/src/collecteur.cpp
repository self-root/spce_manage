#include "collecteur.h"

namespace spce_core {

Collecteur::Collecteur(int id) : Commissionnaire(id)
{

}

Collecteur::Collecteur(const QString &nom, const QString &address, const QString &tel, const QString &email, const QString &responsable, int id)
    : Commissionnaire(nom, address, tel, email, responsable, id)
{

}

bool Collecteur::equal(const BaseEntity &other) const
{
    if (auto *coll = dynamic_cast<const Collecteur*>(&other))
    {
        return Commissionnaire::equal(other);
    }
    return false;
}

} // namespace spce_core
