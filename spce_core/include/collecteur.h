#ifndef COLLECTEUR_H
#define COLLECTEUR_H

#include "spce_core_global.h"
#include "commissionnaire.h"
#include <QString>

namespace spce_core {
class SPCE_CORE_EXPORT Collecteur : public Commissionnaire
{
public:
    Collecteur(int id = -1);
    Collecteur(const QString & nom, const QString &address, const QString &tel, const QString &email, const QString &responsable, int id = -1);

    // BaseEntity interface
public:
    bool equal(const BaseEntity &other) const override;
};
} // namespace spce_core

#endif // COLLECTEUR_H
