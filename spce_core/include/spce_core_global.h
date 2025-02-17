#ifndef SPCE_CORE_GLOBAL_H
#define SPCE_CORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SPCE_CORE_LIBRARY)
#define SPCE_CORE_EXPORT Q_DECL_EXPORT
#else
#define SPCE_CORE_EXPORT Q_DECL_IMPORT
#endif

#endif // SPCE_CORE_GLOBAL_H
