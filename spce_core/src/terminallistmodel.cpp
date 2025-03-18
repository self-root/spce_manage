#include "terminallistmodel.h"
#include "mgtoaport.h"

namespace spce_core {
TerminalListModel::TerminalListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    loadTerminalNames();
}

int TerminalListModel::rowCount(const QModelIndex &parent) const
{
    return terminals.count();
}

QVariant TerminalListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (role == NameRole)
        return terminals.at(row);
    return QVariant();
}

void TerminalListModel::loadTerminalNames()
{
    qDebug() << "Loading terminal names...";
    beginResetModel();
    terminals = MGTOAPort::terminals();
    endResetModel();
    qDebug() << "Terminal count: " << terminals.count();
}

void TerminalListModel::addIfNotExist(const QString terminal)
{

    if (terminal.isEmpty())
        return;
    if (!terminals.contains(terminal))
    {
        qDebug() << "Adding new terminal: " << terminal;
        beginResetModel();
        terminals << terminal;
        MGTOAPort::setTerminals(terminals);
        endResetModel();
    }
}

QHash<int, QByteArray> TerminalListModel::roleNames() const
{
    QHash<int, QByteArray> rolenames;
    rolenames[Roles::NameRole] = "name";
    return rolenames;
}
} // namespace spce_core

