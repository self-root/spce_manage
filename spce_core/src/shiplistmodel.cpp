#include "shiplistmodel.h"
#include <QDir>
#include <flagsvgdownloader.h>

namespace spce_core {
ShipListModel::ShipListModel(APICaller *api, QObject *parent)
    : mApi(api), QAbstractListModel(parent)
{
    QObject::connect(mApi, &APICaller::searchingForShip, this, [&](){setSearching(true);});
    QObject::connect(mApi, &APICaller::shipSearchEnded, this, &ShipListModel::onShipSearchResult);
}

int ShipListModel::rowCount(const QModelIndex &parent) const
{
    return ships.size();
}

QVariant ShipListModel::data(const QModelIndex &index, int role) const
{
    Ship ship = ships.at(index.row());

    switch (role) {
    case Name:
        return ship.name();
    case Flag:
        return ship.flag();
    case FlagUrl:
        return ship.flagUrl();
    case IMO:
        return ship.imo();
    case GrossTonnage:
        return ship.tonnage();
    case Callsign:
        return ship.callSign();
    case ShipType:
        return ship.type();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ShipListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Name] = "name";
    roles[Flag] = "flag";
    roles[FlagUrl] = "flagUrl";
    roles[IMO] = "imo";
    roles[GrossTonnage] = "tonnage";
    roles[Callsign] = "callsign";
    roles[ShipType] = "type";

    return roles;
}

void ShipListModel::searchShip(const QString &shipName)
{
    /*QVector<Ship> res;
    Ship ship;
    ship.setName("Nordic Nanjing");
    ship.setImo("9647291");
    ship.setFlag("Liberia");
    ship.setFlagUrl("lr.svg");
    ship.setType("Bulk Carrier");
    res.append(ship);

    ship.setName("SSI VICTORY");
    ship.setImo("9595943");
    ship.setFlag("Marshall Islands");
    ship.setFlagUrl("mh.svg");
    ship.setType("General Cargo ship");
    res.append(ship);

    ship.setName("FLORETGRACHT");
    ship.setImo("9507611");
    ship.setFlag("Netherlands");
    ship.setFlagUrl("nl.svg");
    ship.setType("Bulk Carrier");
    res.append(ship);

    ship.setName("PETALOUDA");
    ship.setImo("9367669");
    ship.setFlag("Bahamas");
    ship.setFlagUrl("bs.svg");
    ship.setType("Chemical/Oil Products Tanker");
    res.append(ship);

    ship.setName("IVS DUNES");
    ship.setImo("9838515");
    ship.setFlag("Singapore");
    ship.setFlagUrl("sg.svg");
    ship.setType("Vehicles Carrier");
    res.append(ship);

    onShipSearchResult(res);*/
    if (shipName.isEmpty()) return;

    beginResetModel();
    ships.clear();
    endResetModel();
    mApi->searchShip(shipName);

}

void ShipListModel::onShipSearchResult(const QVector<Ship> &results)
{
    setSearching(false);
    beginResetModel();
    ships = results;
    endResetModel();
}

bool ShipListModel::searching() const
{
    return mSearching;
}

void ShipListModel::setSearching(bool newSearching)
{
    if (mSearching == newSearching)
        return;
    mSearching = newSearching;
    emit searchingChanged();
}

} // namespace spce_core
