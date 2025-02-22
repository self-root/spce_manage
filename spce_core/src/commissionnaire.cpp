#include "commissionnaire.h"

namespace spce_core {
Commissionnaire::Commissionnaire() {}

Commissionnaire::Commissionnaire(const QString &nom, const QString &address, const QString &tel, const QString &email, const QString &responsable, int id)
    : BaseEntity(nom, address, tel, email, id), mResponsabble(responsable)
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

} // namespace spce_core

