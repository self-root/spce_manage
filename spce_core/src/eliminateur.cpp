#include "eliminateur.h"

namespace spce_core {
Eliminateur::Eliminateur(int id): Commissionnaire(id) {}

Eliminateur::Eliminateur(const QString &nom, const QString &address, const QString &tel, const QString &email, const QString &responsable, const QString &receptionSite, int id)
    : Commissionnaire(nom, address, tel, email, responsable, id), mReceptionSite(receptionSite)
{

}

QString Eliminateur::receptionSite() const
{
    return mReceptionSite;
}

void Eliminateur::setReceptionSite(const QString &newReceptionSite)
{
    mReceptionSite = newReceptionSite;
}

bool Eliminateur::equal(const BaseEntity &other) const
{
    if (auto *elim = dynamic_cast<const Eliminateur*>(&other))
    {
        if (!Commissionnaire::equal(other))
            return false;

        return mReceptionSite == elim->mReceptionSite;
    }
    return false;
}
} // namespace spce_core

