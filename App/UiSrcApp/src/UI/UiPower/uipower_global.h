#ifndef UIPOWER_GLOBAL_H
#define UIPOWER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UIPOWER_LIBRARY)
#  define UIPOWERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UIPOWERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UIPOWER_GLOBAL_H
