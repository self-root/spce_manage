#ifndef CORECONTROLLER_H
#define CORECONTROLLER_H

#include <QObject>
#include "spce_core_global.h"
#include "apicaller.h"
#include "schedulelistmodel.h"
#include "shipdetailmodel.h"
#include "documentformmodel.h"
#include "documentwriter.h"
#include "shiplistmodel.h"

namespace spce_core {

class SPCE_CORE_EXPORT CoreController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ScheduleListModel *scheduleListModel READ scheduleListModel CONSTANT)
    Q_PROPERTY(ShipDetailModel *shipDetailModel READ shipDetailModel CONSTANT FINAL)
    Q_PROPERTY(DocumentFormModel *documentFormModel READ documentFormModel CONSTANT FINAL)
    Q_PROPERTY(ShipListModel *shipListModel READ shipListModel CONSTANT FINAL)
    Q_PROPERTY(bool fetchingShip READ fetchingShip WRITE setFetchingShip NOTIFY fetchingShipChanged FINAL)
    Q_PROPERTY(QString flagDir READ flagDir CONSTANT FINAL)

public:
    explicit CoreController(QObject *parent = nullptr);
    ScheduleListModel *scheduleListModel() const;

    ShipDetailModel *shipDetailModel() const;

    DocumentFormModel *documentFormModel() const;

    bool fetchingShip() const;
    void setFetchingShip(bool newFetchingShip);

    ShipListModel *shipListModel() const;

    QString flagDir() const;

private:
    APICaller *mApiCaller = nullptr;
    ScheduleListModel *mScheduleListModel = nullptr;
    ShipDetailModel *mShipDetailModel = nullptr;
    DocumentFormModel *mDocumentFormModel = nullptr;
    DocumentWriter *mDocumentWriter = nullptr;
    ShipListModel *mShipListModel = nullptr;

    void openDocumentFolder(const QString &path);
    std::wstring toWideString(const std::string &str);

    bool mFetchingShip = false;
    QString mFlagDir;




private slots:
    void onDocumentsCreated(const QString &documentPath);



signals:
    void fetchingShipChanged();
};
} // namespace spce_core


#endif // CORECONTROLLER_H
