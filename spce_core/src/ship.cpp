#include "ship.h"

namespace spce_core {
Ship::Ship(int id)
    : BaseEntity(id)
{

}

Ship::Ship(const QString &imo, int tonnage, const QString &name, const QString &flag, const QString flagUrl, const QString &callsign, const QString &type, int id)
    : mImo(imo), mTonnage(tonnage), mName(name), mFlag(flag), mFlagUrl(flagUrl), mCallSign(callsign), mType(type), BaseEntity(id)
{}

QString Ship::imo() const
{
    return mImo;
}

void Ship::setImo(const QString &newImo)
{
    mImo = newImo;
}

int Ship::tonnage() const
{
    return mTonnage;
}

void Ship::setTonnage(int newTonnage)
{
    mTonnage = newTonnage;
}

QString Ship::name() const
{
    return mName;
}

void Ship::setName(const QString &newName)
{
    mName = newName;
}

QString Ship::flag() const
{
    return mFlag;
}

void Ship::setFlag(const QString &newFlag)
{
    mFlag = newFlag;
}

QString Ship::flagUrl() const
{
    return mFlagUrl;
}

void Ship::setFlagUrl(const QString &newFlagUrl)
{
    mFlagUrl = newFlagUrl;
}

QString Ship::callSign() const
{
    return mCallSign;
}

void Ship::setCallSign(const QString &newCallSign)
{
    mCallSign = newCallSign;
}

QString Ship::type() const
{
    return mType;
}

void Ship::setType(const QString &newType)
{
    mType = newType;
}

int Ship::year() const
{
    return mYear;
}

void Ship::setYear(int newYear)
{
    mYear = newYear;
}

} // namespace spce_core
