#ifndef UIPLOT_GLOBAL_H
#define UIPLOT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UIPLOT_LIBRARY)
#  define UIPLOTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UIPLOTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UIPLOT_GLOBAL_H
