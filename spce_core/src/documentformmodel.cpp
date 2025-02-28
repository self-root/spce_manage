#include "documentformmodel.h"
#include "databasemanager.h"
namespace spce_core {
DocumentFormModel::DocumentFormModel(QObject *parent)
    : QObject{parent}
{}

void DocumentFormModel::getShip(const QString &imo)
{
    currentShip = DatabaseManager::instance()->mShipDao.getShip(imo);
    setShipPropertyValues();
}

void DocumentFormModel::setShipPropertyValues()
{
    set_imo(currentShip.imo());
    set_shipName(currentShip.name());
    set_flagState(currentShip.flag());
    set_callSign(currentShip.callSign());
    set_shipType(currentShip.type());
    set_tonnage(currentShip.tonnage());
}

} // namespace spce_core
