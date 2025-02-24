#ifndef COMMISSIONNAIRE_H
#define COMMISSIONNAIRE_H

#include "spce_core_global.h"
#include "basebsdentity.h"

namespace spce_core {
class SPCE_CORE_EXPORT Commissionnaire : public BaseBSDEntity
{
public:
    Commissionnaire(int id = -1);
    Commissionnaire(const QString & nom, const QString &address, const QString &tel, const QString &email, const QString &responsable, int id = -1);

    QString responsabble() const;
    void setResponsabble(const QString &newResponsabble);

protected:
    QString mResponsabble;
};
} // namespace spce_core


#endif // COMMISSIONNAIRE_H
