#ifndef _ICURVE_GLOBAL_H
#define _ICURVE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ICURVE_LIBRARY)
#  define ICURVESHARED_EXPORT Q_DECL_EXPORT
#else
#  define ICURVESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif
