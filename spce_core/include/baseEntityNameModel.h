#ifndef BASEENTITYNAMEMODEL_H
#define BASEENTITYNAMEMODEL_H

#include "spce_core_global.h"
#include "basebsdentity.h"
#include <QAbstractListModel>
#include <type_traits>
#include "databasemanager.h"

namespace spce_core {
template <typename T>
class SPCE_CORE_EXPORT BaseEntityNameListModel : public QAbstractListModel
{
public:
    enum Roles{
        NameRole = Qt::UserRole + 1
    };
    BaseEntityNameListModel();
    void getDataFromDb();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    T firstEntity() const;


protected:
    QVector<T> list;
};

template <typename T>
inline BaseEntityNameListModel<T>::BaseEntityNameListModel()
{
    static_assert(std::is_base_of<BaseBSDEntity, T>::value, "T must be a subclass of BaseBSDEntity");
}

template<typename T>
inline void BaseEntityNameListModel<T>::getDataFromDb()
{
    beginResetModel();
    list = DatabaseManager::instance()->getDao<T>().getAll();
    endResetModel();
}

template <typename T>
inline int BaseEntityNameListModel<T>::rowCount(const QModelIndex &parent) const
{
    return list.size();
}

template<typename T>
inline QVariant BaseEntityNameListModel<T>::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    T entity = list.at(row);
    if (role == Qt::DisplayRole || role == Roles::NameRole)
    {
        qDebug() << entity.nom();
        return entity.nom();
    }

    return QVariant();
}

template<typename T>
inline QHash<int, QByteArray> BaseEntityNameListModel<T>::roleNames() const
{
    QHash<int, QByteArray> rolenames;
    rolenames[Roles::NameRole] = "name";
    return rolenames;
}

template<typename T>
inline T BaseEntityNameListModel<T>::firstEntity() const
{
    if (list.size() > 0)
        return list.at(0);
    return T();
}

} // namespace spce_core

#endif // BASEENTITYNAMEMODEL_H
