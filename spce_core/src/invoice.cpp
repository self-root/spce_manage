#include "invoice.h"

namespace spce_core {
Invoice::Invoice(int id): BaseEntity(id) {}

Invoice::Invoice(const QString &number,
                 double quantity,
                 double unitPrice,
                 double amount,
                 const Ship &ship,
                 const QString &item,
                 int id)
    : mNumber(number), mQuantity(quantity), mUnitPrice(unitPrice), mAmount(amount), mShip(ship), mItem(item), BaseEntity(id)
{

}

QString Invoice::number() const
{
    return mNumber;
}

void Invoice::setNumber(const QString &newNumber)
{
    mNumber = newNumber;
}

double Invoice::quantity() const
{
    return mQuantity;
}

void Invoice::setQuantity(double newQuantity)
{
    mQuantity = newQuantity;
}

double Invoice::unitPrice() const
{
    return mUnitPrice;
}

void Invoice::setUnitPrice(double newUnitPrice)
{
    mUnitPrice = newUnitPrice;
}

double Invoice::amount() const
{
    return mAmount;
}

void Invoice::setAmount(double newAmount)
{
    mAmount = newAmount;
}

Ship Invoice::ship() const
{
    return mShip;
}

void Invoice::setShip(const Ship &newShip)
{
    mShip = newShip;
}

QString Invoice::item() const
{
    return mItem;
}

void Invoice::setItem(const QString &newItem)
{
    mItem = newItem;
}
} // namespace spce_core

