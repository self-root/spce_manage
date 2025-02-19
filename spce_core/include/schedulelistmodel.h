#ifndef SCHEDULELISTMODEL_H
#define SCHEDULELISTMODEL_H

#include <QAbstractListModel>
#include "spce_core_global.h"

namespace spce_core {
class Schedule;
class APICaller;
class SPCE_CORE_EXPORT ScheduleListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ScheduleRole{
        ImoRole = Qt::UserRole + 1,
        DateTimeRole,
        TypeRole,
        NameRole,
        FlagUrlRole
    };
    explicit ScheduleListModel(APICaller *api, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void loadSchedules();

private:
    QVector<Schedule> schedule;
    APICaller *mAPI = nullptr;

private slots:
    void onSchedule(const QVector<Schedule> &schedule);
};
} // namespace spce_core


#endif // SCHEDULELISTMODEL_H
