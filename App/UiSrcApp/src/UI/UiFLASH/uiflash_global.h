#ifndef UIFLASH_GLOBAL_H
#define UIFLASH_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UIFLASH_LIBRARY)
#  define UIFLASHSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UIFLASHSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UIFLASH_GLOBAL_H
