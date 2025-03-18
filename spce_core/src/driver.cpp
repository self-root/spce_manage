#include "driver.h"

namespace spce_core {
Driver::Driver(int id)
    : BaseEntity(id)
{}

Driver::Driver(const QString &name, int id)
    : mName(name), BaseEntity(id)
{

}

QString Driver::nom() const
{
    return mName;
}

void Driver::setName(const QString &newName)
{
    mName = newName;
}

} // namespace spce_core
