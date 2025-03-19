#ifndef BASEENTITYLISTMODEL_H
#define BASEENTITYLISTMODEL_H

#include "spce_core_global.h"
#include "baseentity.h"
#include <QAbstractListModel>
#include <type_traits>
#include "databasemanager.h"

namespace spce_core {
template <typename T>
class SPCE_CORE_EXPORT BaseEntityListModel : public QAbstractListModel
{
public:
    enum Roles{
        NameRole = Qt::UserRole + 1
    };
    BaseEntityListModel();
    void getDataFromDb();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    T firstEntity() const;
    T entityAt(int index) const;
    void addOrUpdate(T& entity);

protected:
    QVector<T> list;
};

template <typename T>
inline BaseEntityListModel<T>::BaseEntityListModel()
{
    static_assert(std::is_base_of<BaseEntity, T>::value, "T must be a subclass of BaseEntity");
}

template<typename T>
inline void BaseEntityListModel<T>::getDataFromDb()
{
    beginResetModel();
    list = DatabaseManager::instance()->getDao<T>().getAll();
    endResetModel();
}

template <typename T>
inline int BaseEntityListModel<T>::rowCount(const QModelIndex &parent) const
{
    return list.count();
}

template<typename T>
inline QVariant BaseEntityListModel<T>::data(const QModelIndex &index, int role) const
{
    //static_assert(std::is_base_of<BaseBSDEntity, T>::value, "This method should be overrided if T is not a subclass of BaseBSDEntity");
    int row = index.row();
    T entity = list.at(row);
    if (role == Roles::NameRole)
        return entity.nom();


    return QVariant();
}

template<>
inline QVariant BaseEntityListModel<Vehicle>::data(const QModelIndex &index, int role) const
{
    //static_assert(std::is_base_of<BaseBSDEntity, T>::value, "This method should be overrided if T is not a subclass of BaseBSDEntity");
    int row = index.row();
    Vehicle entity = list.at(row);
    if (role == Roles::NameRole)
        return entity.number();


    return QVariant();
}

template<typename T>
inline QHash<int, QByteArray> BaseEntityListModel<T>::roleNames() const
{
    QHash<int, QByteArray> rolenames;
    rolenames[Roles::NameRole] = "name";
    return rolenames;
}

template<typename T>
inline T BaseEntityListModel<T>::firstEntity() const
{
    if (list.size() > 0)
        return list.at(0);
    return T();
}

template<typename T>
inline T BaseEntityListModel<T>::entityAt(int index) const
{
    if (list.size() > 0 && (index >= 0 && index < list.size()))
        return list.at(index);

    return T();
}

template<typename T>
inline void BaseEntityListModel<T>::addOrUpdate(T &entity)
{
    if (entity.id() < 0)
    {
        qDebug() << "Add new...";
        DatabaseManager::instance()->getDao<T>().add(entity);

    }
    else {
        qDebug() << "Update...";
        DatabaseManager::instance()->getDao<T>().update(entity);
    }
    getDataFromDb();
}

} // namespace spce_core

#endif // BASEENTITYLISTMODEL_H
