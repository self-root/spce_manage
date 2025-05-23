#ifndef INVOICETABLEMODEL_H
#define INVOICETABLEMODEL_H

#include "spce_core_global.h"
#include <QAbstractTableModel>
#include <QDate>
//#include "documentwriter.h"

namespace spce_core {
class DocumentWriter;
class SPCE_CORE_EXPORT InvoiceTableModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(double totalAmount READ totalAmount WRITE setTotalAmount NOTIFY totalAmountChanged FINAL)
    Q_PROPERTY(double totalGarbage READ totalGarbage WRITE setTotalGarbage NOTIFY totalGarbageChanged FINAL)
    Q_PROPERTY(int invoiceCount READ invoiceCount WRITE setInvoiceCount NOTIFY invoiceCountChanged FINAL)
    Q_PROPERTY(QDate startDate READ startDate WRITE setStartDate NOTIFY startDateChanged FINAL)
    Q_PROPERTY(QDate endDate READ endDate WRITE setEndDate NOTIFY endDateChanged FINAL)
public:
    explicit InvoiceTableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void loadData();

    double totalAmount() const;
    void setTotalAmount(double newTotalAmount);

    double totalGarbage() const;
    void setTotalGarbage(double newTotalGarbage);

    int invoiceCount() const;
    void setInvoiceCount(int newInvoiceCount);

    Q_INVOKABLE QVariantMap invoiceAt(int row) const;

    Q_INVOKABLE void updateInvoice(const QVariantMap &data, int row);

    Q_INVOKABLE void deleteInvoice(const QString &invoiceNumber, int row);

    Q_INVOKABLE void toPDF(const QString &invoiceNumber);

    QDate startDate() const;
    void setStartDate(const QDate &newStartDate);

    QDate endDate() const;
    void setEndDate(const QDate &newEndDate);

signals:
    void totalAmountChanged();

    void totalGarbageChanged();

    void invoiceCountChanged();

    void invoiceUpdated();

    void invoicePDFCreated(const QString &filePath);

    void startDateChanged();

    void endDateChanged();

private:
    QVector<QMap<QString, QVariant>> invoices;
    double mTotalAmount = 0.0;
    double mTotalGarbage = 0.0;
    int mInvoiceCount = 0;
    DocumentWriter *writer;
    QDate mStartDate;
    QDate mEndDate;

    void computeTotals();
};
} // namespace spce_core


#endif // INVOICETABLEMODEL_H
