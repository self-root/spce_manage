#ifndef TERMINAL_H
#define TERMINAL_H

#include <baseentity.h>
#include <QString>

namespace spce_core {
class Terminal : public BaseEntity
{
public:
    Terminal();

    QString name() const;
    void setName(const QString &newName);

private:
    QString mName;
};
} // namespace spce_core



#endif // TERMINAL_H
