#ifndef KPPVISION_GLOBAL_H
#define KPPVISION_GLOBAL_H

#include <QtCore/qglobal.h>


#if defined(KPPVISION_LIBRARY)
#  define KPPVISIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define KPPVISIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // KPPVISION_GLOBAL_H
