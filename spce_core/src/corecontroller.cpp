#include "corecontroller.h"
#include "databasemanager.h"

namespace spce_core {
CoreController::CoreController(QObject *parent)
    : QObject{parent},
      mApiCaller(new APICaller),
      mScheduleListModel(new ScheduleListModel(mApiCaller)),
      mShipDetailModel(new ShipDetailModel(mApiCaller))
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
} // namespace spce_core

