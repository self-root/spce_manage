#include "chartmodel.h"
#include "databasemanager.h"

namespace spce_core {
ChartModel::ChartModel(QObject *parent)
    : QObject{parent}
{
    mStartDate = QDate(QDate::currentDate().year(), 1, 1);
    mEndDate = QDate(QDate::currentDate().year(), 12, 31);
}

int ChartModel::shipTypeDistroCount()
{
    return shipTypeDistro.size();
}

void ChartModel::loadData()
{
    shipTypeDistro = DatabaseManager::instance()->mInvoiceDao.getShipTypeDistro(mStartDate, mEndDate);
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

QDate ChartModel::startDate() const
{
    return mStartDate;
}

void ChartModel::setStartDate(const QDate &newStartDate)
{
    if (mStartDate == newStartDate)
        return;
    mStartDate = newStartDate;
    emit startDateChanged();
}

QDate ChartModel::endDate() const
{
    return mEndDate;
}

void ChartModel::setEndDate(const QDate &newEndDate)
{
    if (mEndDate == newEndDate)
        return;
    mEndDate = newEndDate;
    emit endDateChanged();
}

} // namespace spce_core
