#include "apicaller.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "schedule.h"

namespace spce_core {
APICaller::APICaller(QObject *parent)
    : QObject{parent}, mNetworkAccessManager(new QNetworkAccessManager)
{

}

void spce_core::APICaller::fetchShipSchedule()
{
    QNetworkRequest request;
    request.setUrl(baseUrl + "/mgtoa/schedule");
    QNetworkReply *reply = mNetworkAccessManager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, this, &APICaller::onFetchShipScheduleReply);

}

void APICaller::fetchShip(const QString &imo)
{
    QNetworkRequest request;
    request.setUrl(baseUrl + "/mgtoa/ship/" + imo);
    emit fetchingShip(imo);
    QNetworkReply *reply = mNetworkAccessManager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, this, &APICaller::onFetchShipReply);
}

void APICaller::onFetchShipScheduleReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    auto attr = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (attr.isValid())
    {
        int statusCode = attr.toInt();
        switch (statusCode) {
        case 200:{
            QByteArray data = reply->readAll();
            QJsonDocument jDoc = QJsonDocument::fromJson(data);
            QJsonArray jArr = jDoc.array();
            QVector<Schedule> schedule;
            for (QJsonValueConstRef val: jArr)
            {
                QJsonObject obj = val.toObject();
                Schedule aSchedule;
                aSchedule.setDateTime(obj.value("datetime").toString());
                aSchedule.setType(obj.value("type").toString());
                aSchedule.setImo(obj.value("imo").toString());
                aSchedule.setName(obj.value("name").toString());
                aSchedule.setFlagUrl(obj.value("flag_url").toString());

                schedule.append(aSchedule);
            }

            emit shipScheduleFetched(schedule);
            break;
        }
        default:
            break;
        }
    }
}

void APICaller::onFetchShipReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    auto attr = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (attr.isValid())
    {
        int statusCode = attr.toInt();
        switch (statusCode) {
        case 200: {
            QJsonDocument jDoc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject obj = jDoc.object();
            Ship ship(
                obj.value("imo").toString(),
                obj.value("gross_tonnage").toInt(),
                obj.value("name").toString(),
                obj.value("flag").toString(),
                obj.value("flag_url").toString(),
                obj.value("callsign").toString(),
                obj.value("ship_type").toString(),
                obj.value("year").toInt()
            );

            emit shipFetched(ship);
            break;
        }
        default:{
            emit shipFetched(Ship());
            qDebug() << "Ship does not exist or error: " << statusCode;
            break;
        }

        }
    }
}
} // namespace spce_core

