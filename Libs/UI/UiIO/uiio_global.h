#ifndef UIIO_GLOBAL_H
#define UIIO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UIIO_LIBRARY)
#  define UIIOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UIIOSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UIIO_GLOBAL_H
