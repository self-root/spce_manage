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
} // namespace spce_core

