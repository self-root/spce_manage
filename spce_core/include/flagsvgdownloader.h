#ifndef FLAGSVGDOWNLOADER_H
#define FLAGSVGDOWNLOADER_H

#include <QObject>
#include "spce_core_global.h"
#include "schedule.h"

class QNetworkAccessManager;

namespace spce_core {
class SPCE_CORE_EXPORT FlagSVGDownloader : public QObject
{
    Q_OBJECT
public:
    explicit FlagSVGDownloader(QObject *parent = nullptr);
    void downloadFlags(const QVector<Schedule> &schedule);
    void downloadFlag(const QString &flag);
    static QString flagsFolder();
    static bool flagExists(const QString &flagName);
private:
    QNetworkAccessManager *networkAccess = nullptr;
};
} // namespace spce_core


#endif // FLAGSVGDOWNLOADER_H
