#include "collecteur.h"

namespace spce_core {

Collecteur::Collecteur(int id) : Commissionnaire(id)
{

}

Collecteur::Collecteur(const QString &nom, const QString &address, const QString &tel, const QString &email, const QString &responsable, int id)
    : Commissionnaire(nom, address, tel, email, responsable, id)
{

}

} // namespace spce_core
