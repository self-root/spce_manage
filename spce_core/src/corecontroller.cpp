#include "corecontroller.h"
#include "databasemanager.h"


namespace spce_core {
CoreController::CoreController(QObject *parent)
    : QObject{parent},
      mApiCaller(new APICaller),
      mScheduleListModel(new ScheduleListModel(mApiCaller)),
      mShipDetailModel(new ShipDetailModel(mApiCaller)),
    mDocumentFormModel(new DocumentFormModel)
{
    DatabaseManager::instance();
    mScheduleListModel->loadSchedules();
}

ScheduleListModel *CoreController::scheduleListModel() const
{
    return mScheduleListModel;
}

ShipDetailModel *CoreController::shipDetailModel() const
{
    return mShipDetailModel;
}

DocumentFormModel *CoreController::documentFormModel() const
{
    return mDocumentFormModel;
}
} // namespace spce_core

