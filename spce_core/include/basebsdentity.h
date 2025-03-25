#ifndef BASEBSDENTITY_H
#define BASEBSDENTITY_H

#include "spce_core_global.h"
#include "baseentity.h"

#include <QString>

namespace spce_core {
class SPCE_CORE_EXPORT BaseBSDEntity : public BaseEntity
{
public:
    BaseBSDEntity(int id = -1);
    BaseBSDEntity(const QString &nom,
               const QString &address,
               const QString &tel,
               const QString &email,
               int id = -1);

    QString nom() const;
    void setNom(const QString &newNom);

    QString address() const;
    void setAddress(const QString &newAddress);

    QString tel() const;
    void setTel(const QString &newTel);

    QString email() const;
    void setEmail(const QString &newEmail);



protected:
    QString mNom;
    QString mAddress;
    QString mTel;
    QString mEmail;

    // BaseEntity interface
public:
    virtual bool equal(const BaseEntity &other) const override;
};
} // namespace spce_core


#endif // BASEBSDENTITY_H
