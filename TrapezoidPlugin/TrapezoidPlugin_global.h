#ifndef TRAPEZOIDPLUGIN_GLOBAL_H
#define TRAPEZOIDPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TRAPEZOIDPLUGIN_LIBRARY)
#  define TRAPEZOIDPLUGIN_EXPORT Q_DECL_EXPORT
#else
#  define TRAPEZOIDPLUGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // TRAPEZOIDPLUGIN_GLOBAL_H