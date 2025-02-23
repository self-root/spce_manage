#ifndef SHIP_H
#define SHIP_H

#include "spce_core_global.h"
#include "baseentity.h"
#include <QString>

namespace spce_core {
class SPCE_CORE_EXPORT Ship : public BaseEntity
{
public:
    Ship(int id = -1);
    Ship(const QString &imo, int tonnage, const QString &name, const QString &flag, const QString flagUrl, const QString &callsign, const QString &type, int id = -1);

    QString imo() const;
    void setImo(const QString &newImo);

    int tonnage() const;
    void setTonnage(int newTonnage);

    QString name() const;
    void setName(const QString &newName);

    QString flag() const;
    void setFlag(const QString &newFlag);

    QString flagUrl() const;
    void setFlagUrl(const QString &newFlagUrl);

    QString callSign() const;
    void setCallSign(const QString &newCallSign);

    QString type() const;
    void setType(const QString &newType);

    int year() const;
    void setYear(int newYear);

private:
    QString mImo;
    int mTonnage;
    QString mName;
    QString mFlag;
    QString mFlagUrl;
    QString mCallSign;
    QString mType;
    int mYear;
};

} // namespace spce_core

#endif // SHIP_H
