#ifndef SHIPLISTMODEL_H
#define SHIPLISTMODEL_H

#include <QAbstractListModel>
#include "spce_core_global.h"
#include "ship.h"
#include "apicaller.h"

namespace spce_core {
class SPCE_CORE_EXPORT ShipListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool searching READ searching WRITE setSearching NOTIFY searchingChanged FINAL)
public:
    enum ShipRoles{
        Name = Qt::UserRole + 1,
        Flag,
        FlagUrl,
        IMO,
        GrossTonnage,
        Callsign,
        ShipType,
    };
    explicit ShipListModel(APICaller *api, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void searchShip(const QString &shipName);
    Q_INVOKABLE void shipsLike(const QString &name);

    bool searching() const;
    void setSearching(bool newSearching);

signals:
    void searchingChanged();

private slots:
    void onShipSearchResult(const QVector<Ship> &results);

private:
    QVector<Ship> ships;
    APICaller *mApi = nullptr;
    bool mSearching = false;
};
} // namespace spce_core



#endif // SHIPLISTMODEL_H
