

// .NAME __ctkDummyPluginExport - manage Windows system differences
// .SECTION Description
// The __ctkDummyPluginExport captures some system differences between Unix
// and Windows operating systems. 

#ifndef __ctkDummyPluginExport_h
#define __ctkDummyPluginExport_h

#include "ctkCompilerDetections_p.h"

#include <QtGlobal>

#if defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)
#  if defined(CTKDummyPlugin_EXPORTS)
#    define CTK_DUMMY_EXPORT Q_DECL_EXPORT
#  else
#    define CTK_DUMMY_EXPORT Q_DECL_IMPORT
#  endif
#endif

#if !defined(CTK_DUMMY_EXPORT)
//#  if defined(CTK_SHARED)
#    define CTK_DUMMY_EXPORT Q_DECL_EXPORT
//#  else
//#    define CTK_DUMMY_EXPORT
//#  endif
#endif

#endif

