#include "shipdetailmodel.h"
#include "databasemanager.h"
#include "apicaller.h"
#include "flagsvgdownloader.h"
#include <QDir>

namespace spce_core {
ShipDetailModel::ShipDetailModel(APICaller *api, QObject *parent)
    :mApi(api), QObject{parent}
{
    QObject::connect(mApi, &APICaller::shipFetched, this, &ShipDetailModel::onShipDetailFetched);
}

/*QString ShipDetailModel::imo() const
{
    return mImo;
}

void ShipDetailModel::setImo(const QString &newImo)
{
    if (mImo == newImo)
        return;
    mImo = newImo;
    emit imoChanged();
}

void ShipDetailModel::resetImo()
{
    setImo({});
}*/

QString ShipDetailModel::callsign() const
{
    return mCallsign;
}

void ShipDetailModel::setCallsign(const QString &newCallsign)
{
    if (mCallsign == newCallsign)
        return;
    mCallsign = newCallsign;
    emit callsignChanged();
}

void ShipDetailModel::resetCallsign()
{
    setCallsign({});
}

QString ShipDetailModel::flag() const
{
    return mFlag;
}

void ShipDetailModel::setFlag(const QString &newFlag)
{
    if (mFlag == newFlag)
        return;
    mFlag = newFlag;
    emit flagChanged();
}

void ShipDetailModel::resetFlag()
{
    setFlag({});
}

QString ShipDetailModel::flagUrl() const
{
    return QDir::cleanPath(FlagSVGDownloader::flagsFolder() + QDir::separator() + mFlagUrl);
}

void ShipDetailModel::setFlagUrl(const QString &newFlagUrl)
{
    if (mFlagUrl == newFlagUrl)
        return;
    mFlagUrl = newFlagUrl;
    emit flagUrlChanged();
}

void ShipDetailModel::resetFlagUrl()
{
    setFlagUrl({});
}

int ShipDetailModel::grossTonnage() const
{
    return mGrossTonnage;
}

void ShipDetailModel::setGrossTonnage(int newGrossTonnage)
{
    if (mGrossTonnage == newGrossTonnage)
        return;
    mGrossTonnage = newGrossTonnage;
    emit grossTonnageChanged();
}

void ShipDetailModel::resetGrossTonnage()
{
    setGrossTonnage({});
}

QString ShipDetailModel::shipType() const
{
    return mShipType;
}

void ShipDetailModel::setShipType(const QString &newShipType)
{
    if (mShipType == newShipType)
        return;
    mShipType = newShipType;
    emit shipTypeChanged();
}

void ShipDetailModel::resetShipType()
{
    setShipType({});
}

int ShipDetailModel::year() const
{
    return mYear;
}

void ShipDetailModel::setYear(int newYear)
{
    if (mYear == newYear)
        return;
    mYear = newYear;
    emit yearChanged();
}

void ShipDetailModel::resetYear()
{
    setYear({});
}

QString ShipDetailModel::name() const
{
    return mName;
}

void ShipDetailModel::setName(const QString &newName)
{
    if (mName == newName)
        return;
    mName = newName;
    emit nameChanged();
}

void ShipDetailModel::resetName()
{
    setName({});
}

void ShipDetailModel::getShipDetail(const QString &imo)
{
    Ship ship = DatabaseManager::instance()->mShipDao.getShip(imo);
    if (ship.id() > 0)
    {
        currentShip = ship;
        setShipDetails(ship);
        return;
    }

    mApi->fetchShip(imo);

}

void ShipDetailModel::setShipDetails(const Ship &ship)
{
    set_imo(ship.imo());
    setCallsign(ship.callSign());
    setFlag(ship.flag());
    setFlagUrl(ship.flagUrl());
    setGrossTonnage(ship.tonnage());
    setShipType(ship.type());
    setYear(ship.year());
    setName(ship.name());
}

void ShipDetailModel::onShipDetailFetched(const Ship &ship)
{
    currentShip = ship;
    setShipDetails(ship);
    DatabaseManager::instance()->mShipDao.add(currentShip);
}
} // namespace spce_core

