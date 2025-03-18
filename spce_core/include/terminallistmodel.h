#ifndef TERMINALLISTMODEL_H
#define TERMINALLISTMODEL_H

#include <QAbstractListModel>

#include "spce_core_global.h"

namespace spce_core {
class SPCE_CORE_EXPORT TerminalListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles{
        NameRole = Qt::UserRole + 1
    };
    explicit TerminalListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void loadTerminalNames();

    void addIfNotExist(const QString terminal);

    QHash<int, QByteArray> roleNames() const override;

private:
    QStringList terminals;
};
} // namespace spce_core




#endif // TERMINALLISTMODEL_H
