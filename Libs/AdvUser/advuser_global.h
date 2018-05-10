#ifndef ADVUSER_GLOBAL_H
#define ADVUSER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ADVUSER_LIBRARY)
#  define ADVUSERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ADVUSERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ADVUSER_GLOBAL_H
