#ifndef REVENUECHARTMODEL_H
#define REVENUECHARTMODEL_H

#include <QAbstractListModel>
#include <QDate>
#include "spce_core_global.h"

namespace spce_core {
class SPCE_CORE_EXPORT RevenueChartModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QDate startDate READ startDate WRITE setStartDate NOTIFY startDateChanged FINAL)
    Q_PROPERTY(QDate endDate READ endDate WRITE setEndDate NOTIFY endDateChanged FINAL)
public:
    struct RevenueChart
    {
        int month = 0;
        double amount = 0.0;
    };
    enum Roles{
        MonthRole = Qt::UserRole + 1,
        AmountRole,
        GarbageRole,
        ColorRole,
    };

    explicit RevenueChartModel(QObject *parent = nullptr);

    // Basic functionality:
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

     // QAbstractItemModel interface
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void loadData();

    Q_INVOKABLE QVariant dataAt(int row, int role) const;

    QDate startDate() const;
    void setStartDate(const QDate &newStartDate);

    QDate endDate() const;
    void setEndDate(const QDate &newEndDate);

signals:
    void startDateChanged();

    void endDateChanged();

private:
    std::vector<std::pair<QDate, double>> revenueData;
    std::vector<std::pair<QDate, double>> garbageAmountData;
    QHash<int, QString> months{
       {1, "January"},
       { 2 , "February"},
       { 3 , "March"},
       { 4 , "April"},
       { 5 , "May"},
       { 6 , "June"},
       { 7 , "July"},
       { 8 , "August"},
       { 9 , "September"},
       {10 , "October"},
       {11 , "November"},
       {12 , "December"},
    };
    QDate mStartDate;
    QDate mEndDate;
    bool addYear = false;

};
} // namespace spce_core



#endif // REVENUECHARTMODEL_H
