#include "invoicetablemodel.h"
#include "databasemanager.h"
#include "documentwriter.h"
#include "documentformmodel.h"
#include <QLocale>

namespace spce_core {
InvoiceTableModel::InvoiceTableModel(QObject *parent)
    : QAbstractTableModel(parent), writer(new DocumentWriter)
{
    mStartDate = QDate(QDate::currentDate().year(), 1, 1);
    mEndDate = QDate(QDate::currentDate().year(), 12, 31);
}

QVariant InvoiceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            switch (section) {
            case 0:
                return QString("Invoice Number");
            case 1:
                return QString("Quantity (CBM)");
            case 2:
                return QString("Amount (Ar)");
            case 3:
                return QString("Date");
            case 4:
                return QString("Ship Name");
            case 5:
                return QString("Ship type");
            case 6:
                return QString("Flag state");
            default:
                break;
            }
        }
    }
    return QVariant();
}

int InvoiceTableModel::rowCount(const QModelIndex &parent) const
{
    return invoices.size();
}

int InvoiceTableModel::columnCount(const QModelIndex &parent) const
{
    return 7;
}

QVariant InvoiceTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    QMap<QString, QVariant> invoice = invoices.at(index.row());
    QLocale locale;
    switch (index.column()) {
    case 0:
        return invoice["invoice_number"].toString();
    case 1:
        return locale.toString(invoice["quantity"].toDouble());
    case 2:
        return locale.toString(invoice["amount"].toDouble());
    case 3:
        return invoice["i_date"].toString();
    case 4:
        return invoice["ship_name"].toString();
    case 5:
        return invoice["ship_type"].toString();
    case 6:
        return QVariantMap{
            {"text", invoice["flag"].toString()},
            {"url", invoice["flag_url"].toString()}
        };
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> InvoiceTableModel::roleNames() const
{
    return {
            {Qt::DisplayRole, "display"}
    };
}

void InvoiceTableModel::loadData()
{
    beginResetModel();
    invoices = DatabaseManager::instance()->mInvoiceDao.getInvoices(mStartDate, mEndDate);
    endResetModel();
    computeTotals();
    setInvoiceCount(invoices.size());
}

double InvoiceTableModel::totalAmount() const
{
    return mTotalAmount;
}

void InvoiceTableModel::setTotalAmount(double newTotalAmount)
{
    if (qFuzzyCompare(mTotalAmount, newTotalAmount))
        return;
    mTotalAmount = newTotalAmount;
    emit totalAmountChanged();
}

double InvoiceTableModel::totalGarbage() const
{
    return mTotalGarbage;
}

void InvoiceTableModel::setTotalGarbage(double newTotalGarbage)
{
    if (qFuzzyCompare(mTotalGarbage, newTotalGarbage))
        return;
    mTotalGarbage = newTotalGarbage;
    emit totalGarbageChanged();
}

int InvoiceTableModel::invoiceCount() const
{
    return mInvoiceCount;
}

void InvoiceTableModel::setInvoiceCount(int newInvoiceCount)
{
    if (mInvoiceCount == newInvoiceCount)
        return;
    mInvoiceCount = newInvoiceCount;
    emit invoiceCountChanged();
}

QVariantMap InvoiceTableModel::invoiceAt(int row) const
{
    if (row < 0 or row >= invoices.size())
        return QVariantMap();

    return invoices.at(row);

}

void InvoiceTableModel::updateInvoice(const QVariantMap &data, int row)
{
    DatabaseManager::instance()->mInvoiceDao.update(data);
    invoices[row]["amount"] = data["amount"].toDouble();
    invoices[row]["quantity"] = data["quantity"].toDouble();
    emit dataChanged(this->index(row, 0), this->index(row, 3), {Qt::DisplayRole, Qt::EditRole});
    computeTotals();
    emit invoiceUpdated();
}

void InvoiceTableModel::deleteInvoice(const QString &invoiceNumber, int row)
{
    DatabaseManager::instance()->mInvoiceDao.remove(invoiceNumber);
    beginRemoveRows(QModelIndex(), row, row);
    invoices.erase(std::remove_if(invoices.begin(), invoices.end(), [&](QMap<QString, QVariant> &val){
        return val["invoice_number"].toString() == invoiceNumber;
    }), invoices.end());

    endRemoveRows();
    emit invoiceUpdated();
    computeTotals();
    setInvoiceCount(invoices.size());
}

void InvoiceTableModel::toPDF(const QString &invoiceNumber)
{
    for (auto invoice : invoices)
    {
        if (invoice["invoice_number"].toString() == invoiceNumber)
        {
            nlohmann::json data;
            data["ship_name"] = invoice["ship_name"].toString().toStdString();
            data["document_date"] = DocumentFormModel::formatDate(QDate::fromString(invoice["i_date"].toString(), "dd-MM-yyyy")).toStdString();
            data["quantity"] = invoice["quantity"].toString().toStdString();
            data["amount"] = invoice["amount"].toString().toStdString();
            data["invoice_number"] = invoiceNumber.toStdString();
            data["unit_price"] = "";
            data["total"] = invoice["amount"].toString().toStdString();
            writer->writeInvoice(data);
            emit invoicePDFCreated(writer->outPath(invoice["ship_name"].toString()));
            break;
        }
    }
}

QDate InvoiceTableModel::startDate() const
{
    return mStartDate;
}

void InvoiceTableModel::setStartDate(const QDate &newStartDate)
{
    if (mStartDate == newStartDate)
        return;
    mStartDate = newStartDate;
    emit startDateChanged();
    loadData();
    qDebug() << __FUNCTION__ << " New start date: " << newStartDate;
}

QDate InvoiceTableModel::endDate() const
{
    return mEndDate;
}

void InvoiceTableModel::setEndDate(const QDate &newEndDate)
{
    if (mEndDate == newEndDate)
        return;
    mEndDate = newEndDate;
    emit endDateChanged();
    loadData();
}

void InvoiceTableModel::computeTotals()
{
    setTotalAmount(0);
    setTotalGarbage(0);
    double amounts = 0.0;
    double garbages = 0.0;

    for (const auto &i: invoices)
    {
        amounts += i["amount"].toDouble();
        garbages += i["quantity"].toDouble();
    }
    setTotalAmount(amounts);
    setTotalGarbage(garbages);
}

} // namespace spce_core
