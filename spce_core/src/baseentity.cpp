#include "baseentity.h"

namespace spce_core {
BaseEntity::BaseEntity(int id): mId(id) {}

int BaseEntity::id() const
{
    return mId;
}

void BaseEntity::setId(int newId)
{
    mId = newId;
}

bool BaseEntity::equal(const BaseEntity &other) const
{
    return false;
}
} // namespace spce_core

