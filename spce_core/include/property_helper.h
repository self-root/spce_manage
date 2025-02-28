#ifndef PROPERTY_HELPER_H
#define PROPERTY_HELPER_H

#include <QObject>

#define AUTO_PROPERTY(type, name) \
Q_PROPERTY(type name READ name WRITE set_##name NOTIFY name##Changed) \
    public: \
    type name() const { return m_##name; } \
    void set_##name(const type &value) { \
        if (m_##name != value) { \
            m_##name = value; \
            emit name##Changed(); \
    } \
} \
    Q_SIGNAL void name##Changed(); \
    private: \
    type m_##name;

#endif // PROPERTY_HELPER_H
