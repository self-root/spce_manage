#ifndef CORECONTROLLER_H
#define CORECONTROLLER_H

#include <QObject>
#include "spce_core_global.h"
#include "apicaller.h"
#include "schedulelistmodel.h"
#include "documentformmodel.h"
#include "documentwriter.h"
#include "shiplistmodel.h"
#include "invoicetablemodel.h"
#include "revenuechartmodel.h"
#include "chartmodel.h"

namespace spce_core {

class SPCE_CORE_EXPORT CoreController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ScheduleListModel *scheduleListModel READ scheduleListModel CONSTANT)
    Q_PROPERTY(DocumentFormModel *documentFormModel READ documentFormModel CONSTANT FINAL)
    Q_PROPERTY(ShipListModel *shipListModel READ shipListModel CONSTANT FINAL)
    Q_PROPERTY(InvoiceTableModel *invoiceTableModel READ invoiceTableModel CONSTANT FINAL)
    Q_PROPERTY(RevenueChartModel *revenueChartModel READ revenueChartModel CONSTANT FINAL)
    Q_PROPERTY(ChartModel *chartModel READ chartModel CONSTANT FINAL)
    Q_PROPERTY(bool fetchingShip READ fetchingShip WRITE setFetchingShip NOTIFY fetchingShipChanged FINAL)
    Q_PROPERTY(QString flagDir READ flagDir CONSTANT FINAL)
    Q_PROPERTY(QDate startDate READ startDate WRITE setStartDate NOTIFY startDateChanged FINAL)
    Q_PROPERTY(QDate endDate READ endDate WRITE setEndDate NOTIFY endDateChanged FINAL)

public:
    explicit CoreController(QObject *parent = nullptr);
    ScheduleListModel *scheduleListModel() const;

    DocumentFormModel *documentFormModel() const;

    bool fetchingShip() const;
    void setFetchingShip(bool newFetchingShip);

    ShipListModel *shipListModel() const;

    QString flagDir() const;

    InvoiceTableModel *invoiceTableModel() const;

    RevenueChartModel *revenueChartModel() const;

    ChartModel *chartModel() const;

    QDate startDate() const;
    void setStartDate(const QDate &newStartDate);

    QDate endDate() const;
    void setEndDate(const QDate &newEndDate);

private:
    APICaller *mApiCaller = nullptr;
    ScheduleListModel *mScheduleListModel = nullptr;
    DocumentFormModel *mDocumentFormModel = nullptr;
    DocumentWriter *mDocumentWriter = nullptr;
    ShipListModel *mShipListModel = nullptr;
    InvoiceTableModel *mInvoiceTableModel = nullptr;
    RevenueChartModel *mRevenueChartModel = nullptr;
    ChartModel *mChartModel = nullptr;

    void openDocumentFolder(const QString &path);
    std::wstring toWideString(const std::string &str);

    bool mFetchingShip = false;
    QString mFlagDir;

    QDate mStartDate;
    QDate mEndDate;

private slots:
    void onDocumentsCreated(const QString &documentPath);



signals:
    void fetchingShipChanged();
    void startDateChanged();
    void endDateChanged();
};
} // namespace spce_core


#endif // CORECONTROLLER_H
