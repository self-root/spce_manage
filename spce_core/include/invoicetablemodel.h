#ifndef INVOICETABLEMODEL_H
#define INVOICETABLEMODEL_H

#include "spce_core_global.h"
#include <QAbstractTableModel>

namespace spce_core {
class SPCE_CORE_EXPORT InvoiceTableModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(double totalAmount READ totalAmount WRITE setTotalAmount NOTIFY totalAmountChanged FINAL)
    Q_PROPERTY(double totalGarbage READ totalGarbage WRITE setTotalGarbage NOTIFY totalGarbageChanged FINAL)
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

signals:
    void totalAmountChanged();

    void totalGarbageChanged();

    void invoiceCountChanged();

    void invoiceUpdated();

private:
    QVector<QMap<QString, QVariant>> invoices;
    double mTotalAmount = 0.0;
    double mTotalGarbage = 0.0;
    int mInvoiceCount = 0;

    void computeTotals();


    Q_PROPERTY(int invoiceCount READ invoiceCount WRITE setInvoiceCount NOTIFY invoiceCountChanged FINAL)
};
} // namespace spce_core


#endif // INVOICETABLEMODEL_H
