#ifndef DOCUMENTFORMMODEL_H
#define DOCUMENTFORMMODEL_H

#include <QObject>
#include "spce_core_global.h"
#include "property_helper.h"
#include "ship.h"
#include "property_helper.h"
#include "commissionnaire.h"
#include "baseEntityNameModel.h"

namespace spce_core {
class SPCE_CORE_EXPORT DocumentFormModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BaseEntityNameListModel<Commissionnaire> * commListModel READ getCommListModel CONSTANT)
public:
    explicit DocumentFormModel(QObject *parent = nullptr);

    Q_INVOKABLE void getShip(const QString &imo);

    BaseEntityNameListModel<Commissionnaire> *getCommListModel();

private:
    Ship currentShip;
    void setShipPropertyValues();

    AUTO_PROPERTY(QString, imo)
    AUTO_PROPERTY(QString, shipName)
    AUTO_PROPERTY(QString, flagState)
    AUTO_PROPERTY(QString, callSign)
    AUTO_PROPERTY(QString, shipType)
    AUTO_PROPERTY(int, tonnage)

    Commissionnaire currentCommissionnaire;
    void setCommissionnairePropertyValues();
    AUTO_PROPERTY(QString, commAddress);

    BaseEntityNameListModel<Commissionnaire> *commNameListModel = nullptr;
};
} // namespace spce_core


#endif // DOCUMENTFORMMODEL_H
