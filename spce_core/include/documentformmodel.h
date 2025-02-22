#ifndef DOCUMENTFORMMODEL_H
#define DOCUMENTFORMMODEL_H

#include <QObject>
#include "spce_core_global.h"

namespace spce_core {
class SPCE_CORE_EXPORT DocumentFormModel : public QObject
{
    Q_OBJECT
public:
    explicit DocumentFormModel(QObject *parent = nullptr);

signals:
};
} // namespace spce_core


#endif // DOCUMENTFORMMODEL_H
