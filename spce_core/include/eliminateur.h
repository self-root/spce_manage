#ifndef ELIMINATEUR_H
#define ELIMINATEUR_H

#include "spce_core_global.h"
#include "basebsdentity.h"

namespace spce_core {
class SPCE_CORE_EXPORT Eliminateur : public BaseBSDEntity
{
public:
    Eliminateur(int id = -1);
    Eliminateur(const QString &nom, const QString &address, const QString &tel, const QString &email, const QString &receptionSite, int id = -1);

    QString receptionSite() const;
    void setReceptionSite(const QString &newReceptionSite);

private:
    QString mReceptionSite;
};
} // namespace spce_core


#endif // ELIMINATEUR_H
