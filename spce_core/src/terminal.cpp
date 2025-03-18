#include "terminal.h"

namespace spce_core {
Terminal::Terminal() {}

QString Terminal::name() const
{
    return mName;
}

void Terminal::setName(const QString &newName)
{
    mName = newName;
}
} // namespace spce_core

