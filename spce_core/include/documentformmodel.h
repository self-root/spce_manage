#ifndef DOCUMENTFORMMODEL_H
#define DOCUMENTFORMMODEL_H

#include <QObject>
#include "spce_core_global.h"
#include "property_helper.h"
#include "ship.h"
#include "property_helper.h"
#include "commissionnaire.h"
#include "baseEntityListModel.h"
#include "json.hpp"
#include "terminallistmodel.h"
#include "apicaller.h"
#include "flagsvgdownloader.h"

namespace spce_core {
class SPCE_CORE_EXPORT DocumentFormModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BaseEntityListModel<Commissionnaire> * commListModel READ getCommListModel CONSTANT)
    Q_PROPERTY(BaseEntityListModel<Collecteur> * collListModel READ getCollListModel CONSTANT)
    Q_PROPERTY(BaseEntityListModel<Driver> * driverListModel READ getDriverListModel CONSTANT)
    Q_PROPERTY(BaseEntityListModel<Vehicle> *vehicleListModel READ getVehiclListModel CONSTANT)
    Q_PROPERTY(BaseEntityListModel<Eliminateur> *eliminateurListModel READ getEliminateurListModel CONSTANT)
    Q_PROPERTY(TerminalListModel *terminalListModel READ getTerminalListModel CONSTANT)
public:
    explicit DocumentFormModel(APICaller *api,QObject *parent = nullptr);

    Q_INVOKABLE void getShip(const QString &imo);

    BaseEntityListModel<Commissionnaire> *getCommListModel();

    BaseEntityListModel<Collecteur> *getCollListModel();

    BaseEntityListModel<Driver> *getDriverListModel();

    BaseEntityListModel<Vehicle>  *getVehiclListModel();

    BaseEntityListModel<Eliminateur> *getEliminateurListModel();

    TerminalListModel *getTerminalListModel();


    Q_INVOKABLE void commissionnaireAt(int index);

    Q_INVOKABLE void collecteurAt(int index);

    Q_INVOKABLE void vehicleAt(int index);

    Q_INVOKABLE void eliminateurAt(int index);

    Q_INVOKABLE void createDocuments(const QVariantMap &form_data);

    static QString formatDate(const QDate &date);

private:
    APICaller *mApi = nullptr;
    Ship currentShip;
    void setShipPropertyValues();
    FlagSVGDownloader flagDownloader;

    AUTO_PROPERTY(QString, imo)
    AUTO_PROPERTY(QString, shipName)
    AUTO_PROPERTY(QString, flagState)
    AUTO_PROPERTY(QString, callSign)
    AUTO_PROPERTY(QString, shipType)
    AUTO_PROPERTY(int, tonnage)
    AUTO_PROPERTY(QString, flagUrl)

    Commissionnaire currentCommissionnaire;
    void setCommissionnairePropertyValues();
    AUTO_PROPERTY(QString, commAddress);
    AUTO_PROPERTY(QString, commTel);
    AUTO_PROPERTY(QString, commMail);
    AUTO_PROPERTY(QString, commResponsable);

    Collecteur currentCollecteur;
    void setCollecteurPropertyValues();
    AUTO_PROPERTY(QString, collAddress);
    AUTO_PROPERTY(QString, collTel);
    AUTO_PROPERTY(QString, collMail);
    AUTO_PROPERTY(QString, collResponsable);

    Driver currentDriver;
    void setDriverProperyValues();
    AUTO_PROPERTY(QString, driverName);

    Vehicle currentVehicle;
    void setVehicleProperyValues();
    AUTO_PROPERTY(QString, vehicleType);

    Eliminateur currentEliminateur;
    void setEliminateurPropertyValues();
    AUTO_PROPERTY(QString, elimAddress);
    AUTO_PROPERTY(QString, elimTel);
    AUTO_PROPERTY(QString, elimMail);
    AUTO_PROPERTY(QString, elimResponsable);
    AUTO_PROPERTY(QString, elimReceptionSite);

    BaseEntityListModel<Commissionnaire> *commNameListModel = nullptr;
    BaseEntityListModel<Collecteur> *collNameListModel = nullptr;
    BaseEntityListModel<Driver> *driverNameListModel = nullptr;
    BaseEntityListModel<Vehicle>  *vehicleListModel = nullptr;
    BaseEntityListModel<Eliminateur> *eliminateurListModel = nullptr;
    TerminalListModel *terminalListModel = nullptr;

    QString makeInvoiceNumber();

private slots:
    void onShipDetailFetched(const Ship &ship);

signals:
    void writeShipDocument(const nlohmann::json &data);
};

} // namespace spce_core


#endif // DOCUMENTFORMMODEL_H
