#include "commissionnaire.h"

namespace spce_core {
Commissionnaire::Commissionnaire(int id) : BaseBSDEntity(id) {}

Commissionnaire::Commissionnaire(const QString &nom, const QString &address, const QString &tel, const QString &email, const QString &responsable, int id)
    : BaseBSDEntity(nom, address, tel, email, id), mResponsabble(responsable)
{

}

QString Commissionnaire::responsabble() const
{
    return mResponsabble;
}

void Commissionnaire::setResponsabble(const QString &newResponsabble)
{
    mResponsabble = newResponsabble;
}

bool Commissionnaire::equal(const BaseEntity &other) const
{
    if (auto *comm = dynamic_cast<const Commissionnaire*>(&other))
    {
        if (!BaseBSDEntity::equal(other))
            return false;
        else
            return comm->mResponsabble == mResponsabble;
    }
    return false;
}

} // namespace spce_core

