#include "revenuechartmodel.h"
#include "databasemanager.h"
#include "invoice.h"

namespace spce_core {
RevenueChartModel::RevenueChartModel(QObject *parent)
    : QAbstractListModel(parent)
{
    mStartDate = QDate(QDate::currentDate().year(), 1, 1);
    mEndDate = QDate(QDate::currentDate().year(), 12, 31);
}

int RevenueChartModel::rowCount(const QModelIndex &parent) const
{
    return revenueData.size();
}

QVariant RevenueChartModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    std::pair<QDate, double> pair = revenueData.at(index.row());
    switch (role) {
    case MonthRole:
        return pair.first;
    case AmountRole:
        return  pair.second;
    default:
        break;
    }
    return QVariant();
}

QHash<int, QByteArray> RevenueChartModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[MonthRole] = "month";
    roles[AmountRole] = "amount";
    roles[ColorRole] = "color";

    return roles;
}

void RevenueChartModel::loadData()
{
    // Group revenue bu month
    QVector<Invoice> invoices = DatabaseManager::instance()->mInvoiceDao.getAllWithDateRange(mStartDate, mEndDate);
    std::map<QDate, double> rev_data;
    std::map<QDate, double> garbageAmount;
    beginResetModel();
    revenueData.clear();
    garbageAmountData.clear();
    addYear = mStartDate.year() != mEndDate.year();
    for (int i = 0; i < invoices.size(); i++) {
        QDate date = invoices.at(i).date();
        QDate month = addYear ? QDate(date.year(), date.month(), 1) : QDate(2000, date.month(), 1);
        rev_data[month] += invoices.at(i).amount();
        garbageAmount[month] += invoices.at(i).quantity();
    }
    std::copy(rev_data.begin(), rev_data.end(), std::back_inserter(revenueData));
    std::copy(garbageAmount.begin(), garbageAmount.end(), std::back_inserter(garbageAmountData));
    endResetModel();

}

QVariant RevenueChartModel::dataAt(int row, int role) const
{
    std::pair<QDate, double> pair = revenueData.at(row);
    switch (role) {
    case MonthRole:
        if (addYear)
            return pair.first.toString("MMM-yy");
        else
            return pair.first.toString("MMMM");
    case AmountRole:
        return  QVariantList({{pair.second,}});
    case GarbageRole:
        return QVariantList({{garbageAmountData.at(row).second,}});
    default:
        break;
    }
    return QVariant();
}

QDate RevenueChartModel::startDate() const
{
    return mStartDate;
}

void RevenueChartModel::setStartDate(const QDate &newStartDate)
{
    if (mStartDate == newStartDate)
        return;
    mStartDate = newStartDate;
    emit startDateChanged();
    loadData();
}

QDate RevenueChartModel::endDate() const
{
    return mEndDate;
}

void RevenueChartModel::setEndDate(const QDate &newEndDate)
{
    if (mEndDate == newEndDate)
        return;
    mEndDate = newEndDate;
    emit endDateChanged();
    loadData();
}
} // namespace spce_core

