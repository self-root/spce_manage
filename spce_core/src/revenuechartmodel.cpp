#include "revenuechartmodel.h"
#include "databasemanager.h"
#include "invoice.h"

namespace spce_core {
RevenueChartModel::RevenueChartModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int RevenueChartModel::rowCount(const QModelIndex &parent) const
{
    return revenueData.size();
}

QVariant RevenueChartModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    std::pair<int, double> pair = revenueData.at(index.row());
    switch (role) {
    case MonthRole:
        return months[pair.first];
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
    QVector<Invoice> invoices = DatabaseManager::instance()->mInvoiceDao.getAll();
    std::map<int, double> rev_data;
    std::map<int, double> garbageAmount;
    beginResetModel();
    revenueData.clear();
    garbageAmountData.clear();
    for (int i = 0; i < invoices.size(); i++) {
        int month = invoices.at(i).date().month();
        rev_data[month] += invoices.at(i).amount();
        garbageAmount[month] += invoices.at(i).quantity();
    }
    std::copy(rev_data.begin(), rev_data.end(), std::back_inserter(revenueData));
    std::copy(garbageAmount.begin(), garbageAmount.end(), std::back_inserter(garbageAmountData));
    endResetModel();

}

QVariant RevenueChartModel::dataAt(int row, int role) const
{
    std::pair<int, double> pair = revenueData.at(row);
    switch (role) {
    case MonthRole:
        return months[pair.first];
    case AmountRole:
        return  QVariantList({{pair.second,}});
    case GarbageRole:
        return QVariantList({{garbageAmountData.at(row).second,}});
    default:
        break;
    }
    return QVariant();
}
} // namespace spce_core

