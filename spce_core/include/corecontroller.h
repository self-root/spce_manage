#ifndef CORECONTROLLER_H
#define CORECONTROLLER_H

#include <QObject>
#include "spce_core_global.h"
#include "apicaller.h"
#include "schedulelistmodel.h"
#include "shipdetailmodel.h"

namespace spce_core {

class SPCE_CORE_EXPORT CoreController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ScheduleListModel *scheduleListModel READ scheduleListModel CONSTANT)
    Q_PROPERTY(ShipDetailModel *shipDetailModel READ shipDetailModel CONSTANT FINAL)
public:
    explicit CoreController(QObject *parent = nullptr);
    ScheduleListModel *scheduleListModel() const;

    ShipDetailModel *shipDetailModel() const;

private:
    APICaller *mApiCaller = nullptr;
    ScheduleListModel *mScheduleListModel = nullptr;
    ShipDetailModel *mShipDetailModel = nullptr;

signals:
};
} // namespace spce_core


#endif // CORECONTROLLER_H
