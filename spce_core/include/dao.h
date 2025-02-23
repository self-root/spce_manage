#ifndef DAO_H
#define DAO_H

#include "baseentity.h"
#include "spce_core_global.h"
#include <type_traits>

class QSqlDatabase;

namespace spce_core {
template <typename T>
class SPCE_CORE_EXPORT Dao
{
public:
    Dao(QSqlDatabase &database);
    virtual void init() const = 0;
    virtual T get(int id) const = 0;
    virtual void add(T &record) const = 0;
    virtual QVector<T> getAll() const = 0;

protected:
    QSqlDatabase &mDatabase;
};

template <typename T>
Dao<T>::Dao(QSqlDatabase &database)
    : mDatabase(database)
{
    static_assert(std::is_base_of<BaseEntity, T>::value, "T must be a subclass of BaseEntity");
}
} // namespace spce_core



#endif // DAO_H
