#include "schedulelistmodel.h"
#include "schedule.h"
#include "apicaller.h"
#include "flagsvgdownloader.h"
#include <QDir>

namespace spce_core {
ScheduleListModel::ScheduleListModel(APICaller *api, QObject *parent)
    : mAPI(api), QAbstractListModel(parent)
{
    QObject::connect(mAPI, &APICaller::shipScheduleFetched, this, &ScheduleListModel::onSchedule);
}

int ScheduleListModel::rowCount(const QModelIndex &parent) const
{
    return this->schedule.size();
}

QVariant ScheduleListModel::data(const QModelIndex &index, int role) const
{
    Schedule sched = schedule.at(index.row());
    switch (role) {
    case ScheduleRole::ImoRole:
        return sched.imo();
    case ScheduleRole::DateTimeRole:
        return sched.dateTime().toString("dd/MM/yyyy, HH:MM");
    case ScheduleRole::FlagUrlRole:
        return QDir::cleanPath(FlagSVGDownloader::flagsFolder() + QDir::separator() + sched.flagUrl());
    case ScheduleRole::NameRole:
        return sched.name();
    case ScheduleRole::TypeRole:{
        if (sched.type() == ScheduleType::EXPECTED)
            return QString("Expected");
        else
            return QString("Arrival");
    }
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ScheduleListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ScheduleRole::ImoRole] = "imo";
    roles[ScheduleRole::DateTimeRole] = "datetime";
    roles[ScheduleRole::FlagUrlRole] = "flag_url";
    roles[ScheduleRole::TypeRole] = "schedule_type";
    roles[ScheduleRole::NameRole] = "name";

    return roles;
}

void ScheduleListModel::loadSchedules()
{
    mAPI->fetchShipSchedule();
}

void ScheduleListModel::onSchedule(const QVector<Schedule> &schedule)
{
    flagDOwnloader.downloadFlags(schedule);
    beginResetModel();
    this->schedule.clear();
    this->schedule = schedule;
    endResetModel();
    qDebug() << "number of schedules: " << this->schedule.size();
}

} // namespace spce_core

