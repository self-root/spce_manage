#ifndef BASEENTITY_H
#define BASEENTITY_H

#include "spce_core_global.h"

namespace spce_core {
class SPCE_CORE_EXPORT BaseEntity
{
public:
    BaseEntity(int id = -1);

    int id() const;
    void setId(int newId);

private:
    int mId = -1;
};
} // namespace spce_core


#endif // BASEENTITY_H
