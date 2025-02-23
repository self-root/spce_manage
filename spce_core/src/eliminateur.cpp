#include "eliminateur.h"

namespace spce_core {
Eliminateur::Eliminateur() {}

Eliminateur::Eliminateur(const QString &nom, const QString &address, const QString &tel, const QString &email, const QString &receptionSite, int id)
    : BaseBSDEntity(nom, address, tel, email, id), mReceptionSite(receptionSite)
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
} // namespace spce_core

