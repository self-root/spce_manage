#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "spce_core_global.h"
#include <QString>
#include <QDateTime>

namespace spce_core {
enum ScheduleType{
    EXPECTED = 0,
    ARRIVAL
};
class SPCE_CORE_EXPORT Schedule
{
public:


    Schedule();

    QString imo() const;
    void setImo(const QString &newImo);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &newDateTime);
    void setDateTime(const QString &newDatetTme);

    ScheduleType type() const;
    void setType(ScheduleType newType);
    void setType(const QString &newType);

    QString name() const;
    void setName(const QString &newName);

    QString flagUrl() const;
    void setFlagUrl(const QString &newFlagUrl);

private:
    QString mImo;
    QDateTime mDateTime;
    ScheduleType mType;
    QString mName;
    QString mFlagUrl;

};
} // namespace spce_core


#endif // SCHEDULE_H
