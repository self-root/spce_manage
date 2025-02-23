#include "basebsdentity.h"

namespace spce_core {
BaseBSDEntity::BaseBSDEntity() {}

BaseBSDEntity::BaseBSDEntity(const QString &nom, const QString &address, const QString &tel, const QString &email, int id)
    : mNom(nom), mAddress(address), mTel(tel), mEmail(email), BaseEntity(id)
{

}
QString BaseBSDEntity::nom() const
{
    return mNom;
}

void BaseBSDEntity::setNom(const QString &newNom)
{
    mNom = newNom;
}

QString BaseBSDEntity::address() const
{
    return mAddress;
}

void BaseBSDEntity::setAddress(const QString &newAddress)
{
    mAddress = newAddress;
}

QString BaseBSDEntity::tel() const
{
    return mTel;
}

void BaseBSDEntity::setTel(const QString &newTel)
{
    mTel = newTel;
}

QString BaseBSDEntity::email() const
{
    return mEmail;
}

void BaseBSDEntity::setEmail(const QString &newEmail)
{
    mEmail = newEmail;
}


}
