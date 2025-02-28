#ifndef CORECONTROLLER_H
#define CORECONTROLLER_H

#include <QObject>
#include "spce_core_global.h"
#include "apicaller.h"
#include "schedulelistmodel.h"
#include "shipdetailmodel.h"
#include "documentformmodel.h"

namespace spce_core {

class SPCE_CORE_EXPORT CoreController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ScheduleListModel *scheduleListModel READ scheduleListModel CONSTANT)
    Q_PROPERTY(ShipDetailModel *shipDetailModel READ shipDetailModel CONSTANT FINAL)
    Q_PROPERTY(DocumentFormModel *documentFormModel READ documentFormModel CONSTANT FINAL)
public:
    explicit CoreController(QObject *parent = nullptr);
    ScheduleListModel *scheduleListModel() const;

    ShipDetailModel *shipDetailModel() const;

    DocumentFormModel *documentFormModel() const;

private:
    APICaller *mApiCaller = nullptr;
    ScheduleListModel *mScheduleListModel = nullptr;
    ShipDetailModel *mShipDetailModel = nullptr;
    DocumentFormModel *mDocumentFormModel = nullptr;



signals:
};
} // namespace spce_core


#endif // CORECONTROLLER_H
