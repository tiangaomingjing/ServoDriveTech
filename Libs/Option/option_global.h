#ifndef OPTION_GLOBAL_H
#define OPTION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(OPTION_LIBRARY)
#  define OPTIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define OPTIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // OPTION_GLOBAL_H
