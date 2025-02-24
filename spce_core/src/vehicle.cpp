#include "vehicle.h"



namespace spce_core {
Vehicle::Vehicle(int id)
    : BaseEntity(id)
{}

Vehicle::Vehicle(const QString &type, const QString &number, int id)
    : mType(type), mNumber(number), BaseEntity(id)
{}
QString Vehicle::type() const
{
    return mType;
}

void Vehicle::setType(const QString &newType)
{
    mType = newType;
}

QString Vehicle::number() const
{
    return mNumber;
}

void Vehicle::setNumber(const QString &newNumber)
{
    mNumber = newNumber;
}

}
