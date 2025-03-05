#include "documentformmodel.h"
#include "databasemanager.h"

namespace spce_core {
DocumentFormModel::DocumentFormModel(QObject *parent)
    : QObject{parent}, commNameListModel(new BaseEntityNameListModel<Commissionnaire>)
{
    commNameListModel->getDataFromDb();
    currentCommissionnaire = commNameListModel->firstEntity();
    setCommissionnairePropertyValues();
}

void DocumentFormModel::getShip(const QString &imo)
{
    currentShip = DatabaseManager::instance()->mShipDao.getShip(imo);
    setShipPropertyValues();
}

BaseEntityNameListModel<Commissionnaire> *DocumentFormModel::getCommListModel()
{
    return commNameListModel;
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

void DocumentFormModel::setCommissionnairePropertyValues()
{
    set_commAddress(currentCommissionnaire.address());
}

} // namespace spce_core
