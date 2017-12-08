#ifndef UIRAM_GLOBAL_H
#define UIRAM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UIRAM_LIBRARY)
#  define UIRAMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UIRAMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UIRAM_GLOBAL_H
