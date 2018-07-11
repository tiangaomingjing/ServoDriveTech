#ifndef SDKERNEL_GLOBAL_H
#define SDKERNEL_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QTreeWidget>

#if defined(SDKERNEL_LIBRARY)
#  define SDKERNELSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SDKERNELSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SDKERNEL_GLOBAL_H
