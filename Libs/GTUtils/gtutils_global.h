#ifndef UTILS_GLOBAL_H
#define UTILS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GTUTILS_LIBRARY)
#  define GTUTILSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GTUTILSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UTILS_GLOBAL_H
