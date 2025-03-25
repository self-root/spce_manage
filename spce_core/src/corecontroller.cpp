#include "corecontroller.h"
#include "databasemanager.h"
#include <windows.h>
#include "flagsvgdownloader.h"


namespace spce_core {
CoreController::CoreController(QObject *parent)
    : QObject{parent},
      mApiCaller(new APICaller),
      mScheduleListModel(new ScheduleListModel(mApiCaller)),
      mDocumentFormModel(new DocumentFormModel(mApiCaller)),
      mDocumentWriter(new DocumentWriter),
      mShipListModel(new ShipListModel(mApiCaller)),
      mFlagDir(FlagSVGDownloader::flagsFolder()),
      mInvoiceTableModel(new InvoiceTableModel),
      mRevenueChartModel(new RevenueChartModel),
      mChartModel(new ChartModel)
{
    DatabaseManager::instance();
    mScheduleListModel->loadSchedules();

    QObject::connect(mDocumentFormModel, &DocumentFormModel::writeShipDocument, mDocumentWriter, &DocumentWriter::write);
    QObject::connect(mDocumentWriter, &DocumentWriter::documentsCreated, this, &CoreController::onDocumentsCreated);
    QObject::connect(mInvoiceTableModel, &InvoiceTableModel::invoicePDFCreated, this, &CoreController::onDocumentsCreated);
    QObject::connect(mApiCaller, &APICaller::fetchingShip, this, [&](){setFetchingShip(true);});
    QObject::connect(mApiCaller, &APICaller::shipFetched, this, [&](){setFetchingShip(false);});
}

ScheduleListModel *CoreController::scheduleListModel() const
{
    return mScheduleListModel;
}

DocumentFormModel *CoreController::documentFormModel() const
{
    return mDocumentFormModel;
}

void CoreController::openDocumentFolder(const QString &path)
{
    std::wstring action = toWideString("open");
    std::wstring dir = toWideString(path.toStdString());
    ShellExecute(NULL, action.c_str(), dir.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

std::wstring CoreController::toWideString(const std::string &str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);
    return wstr;
}

QString CoreController::flagDir() const
{
    return mFlagDir;
}

InvoiceTableModel *CoreController::invoiceTableModel() const
{
    return mInvoiceTableModel;
}

RevenueChartModel *CoreController::revenueChartModel() const
{
    return mRevenueChartModel;
}

ChartModel *CoreController::chartModel() const
{
    return mChartModel;
}

bool CoreController::fetchingShip() const
{
    return mFetchingShip;
}

void CoreController::setFetchingShip(bool newFetchingShip)
{
    if (mFetchingShip == newFetchingShip)
        return;
    mFetchingShip = newFetchingShip;
    emit fetchingShipChanged();
}

ShipListModel *CoreController::shipListModel() const
{
    return mShipListModel;
}

void CoreController::onDocumentsCreated(const QString &documentPath)
{
    this->openDocumentFolder(documentPath);
}
} // namespace spce_core

