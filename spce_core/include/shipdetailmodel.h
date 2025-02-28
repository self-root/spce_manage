#ifndef SHIPDETAILMODEL_H
#define SHIPDETAILMODEL_H

#include <QObject>
#include "spce_core_global.h"
#include "ship.h"
#include "property_helper.h"

namespace spce_core {
class APICaller;
class SPCE_CORE_EXPORT ShipDetailModel : public QObject
{
    Q_OBJECT

    //Q_PROPERTY(QString imo READ imo WRITE setImo RESET resetImo NOTIFY imoChanged FINAL)
    Q_PROPERTY(QString callsign READ callsign WRITE setCallsign RESET resetCallsign NOTIFY callsignChanged FINAL)
    Q_PROPERTY(QString flag READ flag WRITE setFlag RESET resetFlag NOTIFY flagChanged FINAL)
    Q_PROPERTY(QString flagUrl READ flagUrl WRITE setFlagUrl RESET resetFlagUrl NOTIFY flagUrlChanged FINAL)
    Q_PROPERTY(int grossTonnage READ grossTonnage WRITE setGrossTonnage RESET resetGrossTonnage NOTIFY grossTonnageChanged FINAL)
    Q_PROPERTY(QString shipType READ shipType WRITE setShipType RESET resetShipType NOTIFY shipTypeChanged FINAL)
    Q_PROPERTY(int year READ year WRITE setYear RESET resetYear NOTIFY yearChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName RESET resetName NOTIFY nameChanged FINAL)
public:
    explicit ShipDetailModel(APICaller *api, QObject *parent = nullptr);
    //QString imo() const;
    //void setImo(const QString &newImo);
    //void resetImo();


    QString callsign() const;
    void setCallsign(const QString &newCallsign);
    void resetCallsign();

    QString flag() const;
    void setFlag(const QString &newFlag);
    void resetFlag();

    QString flagUrl() const;
    void setFlagUrl(const QString &newFlagUrl);
    void resetFlagUrl();

    int grossTonnage() const;
    void setGrossTonnage(int newGrossTonnage);
    void resetGrossTonnage();

    QString shipType() const;
    void setShipType(const QString &newShipType);
    void resetShipType();

    int year() const;
    void setYear(int newYear);
    void resetYear();

    QString name() const;
    void setName(const QString &newName);
    void resetName();

    Q_INVOKABLE void getShipDetail(const QString &imo);
    void setShipDetails(const Ship &ship);

private slots:
    void onShipDetailFetched(const Ship &ship);

signals:
    //void imoChanged();
    void callsignChanged();
    void flagChanged();
    void flagUrlChanged();
    void grossTonnageChanged();
    void shipTypeChanged();
    void yearChanged();
    void nameChanged();

private:
    Ship currentShip;
    QString mImo;
    QString mCallsign;
    QString mFlag;
    QString mFlagUrl;
    int mGrossTonnage = 0;
    QString mShipType;
    int mYear = 0;
    QString mName;

    APICaller *mApi = nullptr;


AUTO_PROPERTY(QString, imo)
};
}


#endif // SHIPDETAILMODEL_H
