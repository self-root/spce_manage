#ifndef INVOICE_H
#define INVOICE_H

#include <baseentity.h>
#include "spce_core_global.h"
#include "ship.h"

#include <QDate>

namespace spce_core {
class SPCE_CORE_EXPORT Invoice : public BaseEntity
{
public:
    Invoice(int id = -1);
    Invoice(const QString &number,double quantity, double unitPrice, double amount ,const Ship &ship, const QString &item, const QDate &date, int id = -1);

    QString number() const;
    void setNumber(const QString &newNumber);
    double quantity() const;
    void setQuantity(double newQuantity);
    double unitPrice() const;
    void setUnitPrice(double newUnitPrice);
    double amount() const;
    void setAmount(double newAmount);
    Ship ship() const;
    void setShip(const Ship &newShip);

    QString item() const;
    void setItem(const QString &newItem);

    QDate date() const;
    void setDate(const QDate &newDate);

private:
    QString mNumber;
    double mQuantity;
    double mUnitPrice;
    double mAmount;
    Ship mShip;
    QString mItem;
    QDate mDate;
};
} // namespace spce_core



#endif // INVOICE_H
