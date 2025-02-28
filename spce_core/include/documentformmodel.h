#ifndef DOCUMENTFORMMODEL_H
#define DOCUMENTFORMMODEL_H

#include <QObject>
#include "spce_core_global.h"
#include "property_helper.h"
#include "ship.h"

namespace spce_core {
class SPCE_CORE_EXPORT DocumentFormModel : public QObject
{
    Q_OBJECT
public:
    explicit DocumentFormModel(QObject *parent = nullptr);

    Q_INVOKABLE void getShip(const QString &imo);

private:
    Ship currentShip;
    void setShipPropertyValues();

    AUTO_PROPERTY(QString, imo)
    AUTO_PROPERTY(QString, shipName)
    AUTO_PROPERTY(QString, flagState)
    AUTO_PROPERTY(QString, callSign)
    AUTO_PROPERTY(QString, shipType)
    AUTO_PROPERTY(int, tonnage)
};
} // namespace spce_core


#endif // DOCUMENTFORMMODEL_H
