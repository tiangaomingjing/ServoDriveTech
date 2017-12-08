#ifndef UIBRAKE_GLOBAL_H
#define UIBRAKE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UIBRAKE_LIBRARY)
#  define UIBRAKESHARED_EXPORT Q_DECL_EXPORT
#else
#  define UIBRAKESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UIBRAKE_GLOBAL_H
