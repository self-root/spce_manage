#include "corecontroller.h"

namespace spce_core {
CoreController::CoreController(QObject *parent)
    : QObject{parent}, mApiCaller(new APICaller), mScheduleListModel(new ScheduleListModel(mApiCaller))
{
    mScheduleListModel->loadSchedules();
}

ScheduleListModel *CoreController::scheduleListModel() const
{
    return mScheduleListModel;
}
} // namespace spce_core

