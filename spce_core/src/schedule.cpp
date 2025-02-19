#include "schedule.h"

namespace spce_core {
Schedule::Schedule() {}

QString Schedule::imo() const
{
    return mImo;
}

void Schedule::setImo(const QString &newImo)
{
    mImo = newImo;
}

QDateTime Schedule::dateTime() const
{
    return mDateTime;
}

void Schedule::setDateTime(const QDateTime &newDateTime)
{
    mDateTime = newDateTime;
}

void Schedule::setDateTime(const QString &newDatetTme)
{
    QDateTime nDateTime = QDateTime::fromString(newDatetTme, "dd/MM/yyyy HH:mm");
    setDateTime((nDateTime));
}

ScheduleType Schedule::type() const
{
    return mType;
}

void Schedule::setType(ScheduleType newType)
{
    mType = newType;
}

void Schedule::setType(const QString &newType)
{
    if (newType == "expected")
        setType(ScheduleType::EXPECTED);
    else
        setType(ScheduleType::ARRIVAL);
}

QString Schedule::name() const
{
    return mName;
}

void Schedule::setName(const QString &newName)
{
    mName = newName;
}

QString Schedule::flagUrl() const
{
    return mFlagUrl;
}

void Schedule::setFlagUrl(const QString &newFlagUrl)
{
    mFlagUrl = newFlagUrl;
}
} // namespace spce_core

