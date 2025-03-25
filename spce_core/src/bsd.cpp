#include "bsd.h"

namespace spce_core {
BSD::BSD(int id) : BaseEntity(id)
{

}

BSD::BSD(const Commissionnaire &commissionnaire, const Collecteur &collecteur, const Eliminateur &eliminateur, const Driver &driver, const Vehicle &vehicle, const Ship &ship, const QDate &date, int invoiceID, int id)
    : mCommissionnaire(commissionnaire),
    mCollecteur(collecteur),
    mEliminateur(eliminateur),
    mDriver(driver),
    mVehicle(vehicle),
    mShip(ship),
    mDate(date),
    mInvoiceId(invoiceID),
    BaseEntity(id)
{

}

Commissionnaire BSD::commissionnaire() const
{
    return mCommissionnaire;
}

void BSD::setCommissionnaire(const Commissionnaire &newCommissionnaire)
{
    mCommissionnaire = newCommissionnaire;
}

Collecteur BSD::collecteur() const
{
    return mCollecteur;
}

void BSD::setCollecteur(const Collecteur &newCollecteur)
{
    mCollecteur = newCollecteur;
}

Eliminateur BSD::eliminateur() const
{
    return mEliminateur;
}

void BSD::setEliminateur(const Eliminateur &newEliminateur)
{
    mEliminateur = newEliminateur;
}

Driver BSD::driver() const
{
    return mDriver;
}

void BSD::setDriver(const Driver &newDriver)
{
    mDriver = newDriver;
}

Vehicle BSD::vehicle() const
{
    return mVehicle;
}

void BSD::setVehicle(const Vehicle &newVehicle)
{
    mVehicle = newVehicle;
}

Ship BSD::ship() const
{
    return mShip;
}

void BSD::setShip(const Ship &newShip)
{
    mShip = newShip;
}

QDate BSD::date() const
{
    return mDate;
}

void BSD::setDate(const QDate &newDate)
{
    mDate = newDate;
}

int BSD::invoiceId() const
{
    return mInvoiceId;
}

void BSD::setInvoiceId(int newInvoiceId)
{
    mInvoiceId = newInvoiceId;
}



} // namespace spce_core

