#include "apicaller.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

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
            QVector<QMap<QString, QString>> schedule;
            for (QJsonValueConstRef val: jArr)
            {
                QJsonObject obj = val.toObject();
                QMap<QString, QString> aSchedule;
                aSchedule["datetime"] = obj.value("datetime").toString();
                aSchedule["type"] = obj.value("type").toString();
                aSchedule["imo"] = obj.value("imo").toString();
                aSchedule["name"] = obj.value("name").toString();
                aSchedule["flag_url"] = obj.value("flag_url").toString();

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
} // namespace spce_core

