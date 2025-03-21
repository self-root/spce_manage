#include "flagsvgdownloader.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace spce_core {
FlagSVGDownloader::FlagSVGDownloader(QObject *parent)
    : QObject{parent}, networkAccess(new QNetworkAccessManager)
{}

void FlagSVGDownloader::downloadFlags(const QVector<Schedule> &schedule)
{
    qDebug() << "Downloading flags";
    for (const Schedule &aschedule : schedule)
    {
        QString flagName = aschedule.flagUrl();
        if (!flagExists(flagName))
        {
            qDebug() << flagName << " does not exists, downloading...";
            downloadFlag(flagName);
        }
    }
}

void FlagSVGDownloader::downloadFlag(const QString &flag)
{
    QNetworkRequest request;
    request.setUrl("https://static.vesselfinder.net/images/flags/4x3/" + flag);
    qDebug() << "Downloading flag: " << request.url();
    QNetworkReply *reply = networkAccess->get(request);

    QObject::connect(reply, &QNetworkReply::finished, this, [flag, reply](){
        //QNetworkReply *nReply = qobject_cast<QNetworkReply*>(QObject::sender());
        qDebug() << "Flag: " << flag;
        auto attr = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if (attr.isValid())
        {
            int statusCode = attr.toInt();
            if (statusCode == 200)
            {
                QByteArray data = reply->readAll();
                qDebug() << "Data: " << data;
                QFile file(QDir::cleanPath(flagsFolder() + QDir::separator() + flag));
                if (file.open(QIODevice::WriteOnly))
                {
                    file.write(data);
                    file.close();
                }
            }
            else
            {
                qDebug() << "Flag download errorcode: " << statusCode;
            }
        }
    });
}

QString FlagSVGDownloader::flagsFolder()
{
    QStringList locations = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    QString appDataLocation = locations.first();
    QString flagDirPath = QDir::cleanPath(appDataLocation + QDir::separator() + "flags");
    QDir flagDir(flagDirPath);
    if (!flagDir.exists())
        flagDir.mkpath(flagDirPath);

    return flagDirPath;
}

bool FlagSVGDownloader::flagExists(const QString &flagName)
{
    QString flagPath = QDir::cleanPath(flagsFolder() + QDir::separator() + flagName);
    return QFileInfo::exists(flagPath);
}

} // namespace spce_core
