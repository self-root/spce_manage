#ifndef BSD_H
#define BSD_H

#include <baseentity.h>
#include "spce_core_global.h"
#include "collecteur.h"
#include "commissionnaire.h"
#include "driver.h"
#include "vehicle.h"
#include "ship.h"
#include "eliminateur.h"

#include <QDate>

namespace spce_core {
class SPCE_CORE_EXPORT BSD : public BaseEntity
{
public:
    BSD(int id = -1);
    BSD(const Commissionnaire &commissionnaire, const Collecteur &collecteur, const Eliminateur &eliminateur, const Driver &driver, const Vehicle &vehicle, const Ship &ship, const QDate &date, int id = -1);

    Commissionnaire commissionnaire() const;
    void setCommissionnaire(const Commissionnaire &newCommissionnaire);
    Collecteur collecteur() const;
    void setCollecteur(const Collecteur &newCollecteur);
    Eliminateur eliminateur() const;
    void setEliminateur(const Eliminateur &newEliminateur);
    Driver driver() const;
    void setDriver(const Driver &newDriver);
    Vehicle vehicle() const;
    void setVehicle(const Vehicle &newVehicle);
    Ship ship() const;
    void setShip(const Ship &newShip);
    QDate date() const;
    void setDate(const QDate &newDate);

private:
    Commissionnaire mCommissionnaire;
    Collecteur mCollecteur;
    Eliminateur mEliminateur;
    Driver mDriver;
    Vehicle mVehicle;
    Ship mShip;
    QDate mDate;
};
} // namespace spce_core


#endif // BSD_H
