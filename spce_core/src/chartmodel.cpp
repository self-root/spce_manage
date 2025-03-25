#include "chartmodel.h"
#include "databasemanager.h"

namespace spce_core {
ChartModel::ChartModel(QObject *parent)
    : QObject{parent}
{}

int ChartModel::shipTypeDistroCount()
{
    return shipTypeDistro.size();
}

void ChartModel::loadData()
{
    shipTypeDistro = DatabaseManager::instance()->mInvoiceDao.getShipTypeDistro();
}

QVariant ChartModel::dataAt(int index, int role)
{
    if (index < 0)
        return QVariant();

    auto pair = shipTypeDistro.at(index);
    switch (role) {
    case TypeRole:
        return pair.first;
    case CountRole:
        return pair.second;
    default:
        break;
    }
    return QVariant();
}

} // namespace spce_core
