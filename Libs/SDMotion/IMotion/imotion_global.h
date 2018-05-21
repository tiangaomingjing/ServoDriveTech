#ifndef IMOTION_GLOBAL_H
#define IMOTION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(IMOTION_LIBRARY)
#  define IMOTIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define IMOTIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // IMOTION_GLOBAL_H
