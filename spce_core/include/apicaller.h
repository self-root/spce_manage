#ifndef APICALLER_H
#define APICALLER_H

#include "spce_core_global.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include "schedule.h"
#include "ship.h"

class QNetworkAccessManager;
namespace spce_core {
class SPCE_CORE_EXPORT APICaller : public QObject
{
    Q_OBJECT
public:
    explicit APICaller(QObject *parent = nullptr);
    void fetchShipSchedule();
    void fetchShip(const QString &imo);
    void searchShip(const QString &shipName);
private:
    QString baseUrl = "http://212.24.111.24:8002";
    QNetworkAccessManager *mNetworkAccessManager = nullptr;

private slots:
    void onFetchShipScheduleReply();
    void onFetchShipReply();
    void onShipSearchReply();
signals:
    void shipScheduleFetched(const QVector<Schedule> &schedule);
    void shipFetched(const Ship &ship);
    void fetchingShip(const QString &parameter);
    void searchingForShip(const QString &shipName);
    void shipSearchEnded(const QVector<Ship> &ships);
};

} // namespace spce_core


#endif // APICALLER_H
