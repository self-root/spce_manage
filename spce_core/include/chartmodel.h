#ifndef CHARTMODEL_H
#define CHARTMODEL_H

#include "spce_core_global.h"
#include <QObject>
#include <QMap>
#include <QDate>

namespace spce_core {
class SPCE_CORE_EXPORT ChartModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDate startDate READ startDate WRITE setStartDate NOTIFY startDateChanged FINAL)
    Q_PROPERTY(QDate endDate READ endDate WRITE setEndDate NOTIFY endDateChanged FINAL)
public:
    enum Roles{
        TypeRole = Qt::UserRole + 1,
        CountRole
    };
    explicit ChartModel(QObject *parent = nullptr);
    Q_INVOKABLE int shipTypeDistroCount();

    Q_INVOKABLE void loadData();

    Q_INVOKABLE QVariant dataAt(int index, int role);

    QDate startDate() const;
    void setStartDate(const QDate &newStartDAte);

    QDate endDate() const;
    void setEndDate(const QDate &newEndDate);

signals:
    void startDateChanged();

    void endDateChanged();

private:
    QVector<QPair<QString, int>> shipTypeDistro;
    QDate mStartDate;
    QDate mEndDate;
};
} // namespace spce_core


#endif // CHARTMODEL_H
