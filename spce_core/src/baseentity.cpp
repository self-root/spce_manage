#include "baseentity.h"

namespace spce_core {
BaseEntity::BaseEntity() {}

BaseEntity::BaseEntity(const QString &nom, const QString &address, const QString &tel, const QString &email, int id)
    : mNom(nom), mAddress(address), mTel(tel), mEmail(email), mId(id)
{

}
QString BaseEntity::nom() const
{
    return mNom;
}

void BaseEntity::setNom(const QString &newNom)
{
    mNom = newNom;
}

QString BaseEntity::address() const
{
    return mAddress;
}

void BaseEntity::setAddress(const QString &newAddress)
{
    mAddress = newAddress;
}

QString BaseEntity::tel() const
{
    return mTel;
}

void BaseEntity::setTel(const QString &newTel)
{
    mTel = newTel;
}

QString BaseEntity::email() const
{
    return mEmail;
}

void BaseEntity::setEmail(const QString &newEmail)
{
    mEmail = newEmail;
}

int BaseEntity::id() const
{
    return mId;
}

void BaseEntity::setId(int newId)
{
    mId = newId;
}

}
