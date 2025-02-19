#ifndef APICALLER_H
#define APICALLER_H

#include "spce_core_global.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include "schedule.h"

class QNetworkAccessManager;
namespace spce_core {
class SPCE_CORE_EXPORT APICaller : public QObject
{
    Q_OBJECT
public:
    explicit APICaller(QObject *parent = nullptr);
    void fetchShipSchedule();
private:
    QString baseUrl = "http://0.0.0.0:8000";
    QNetworkAccessManager *mNetworkAccessManager = nullptr;

private slots:
    void onFetchShipScheduleReply();
signals:
    void shipScheduleFetched(const QVector<Schedule> &schedule);
};

} // namespace spce_core


#endif // APICALLER_H
