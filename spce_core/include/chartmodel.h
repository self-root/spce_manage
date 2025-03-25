#ifndef CHARTMODEL_H
#define CHARTMODEL_H

#include "spce_core_global.h"
#include <QObject>
#include <QMap>

namespace spce_core {
class SPCE_CORE_EXPORT ChartModel : public QObject
{
    Q_OBJECT
public:
    enum Roles{
        TypeRole = Qt::UserRole + 1,
        CountRole
    };
    explicit ChartModel(QObject *parent = nullptr);
    Q_INVOKABLE int shipTypeDistroCount();

    Q_INVOKABLE void loadData();

    Q_INVOKABLE QVariant dataAt(int index, int role);

private:
    QVector<QPair<QString, int>> shipTypeDistro;
};
} // namespace spce_core


#endif // CHARTMODEL_H
