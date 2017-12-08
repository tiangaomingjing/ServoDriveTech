#ifndef UIMOTOR_GLOBAL_H
#define UIMOTOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UIMOTOR_LIBRARY)
#  define UIMOTORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UIMOTORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UIMOTOR_GLOBAL_H
