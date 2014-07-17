#ifndef ICXMLSERIALIZABLE_GLOBAL_H
#define ICXMLSERIALIZABLE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ICXMLSERIALIZABLE_LIBRARY)
#  define ICXMLSERIALIZABLESHARED_EXPORT Q_DECL_EXPORT
#else
#  define ICXMLSERIALIZABLESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ICXMLSERIALIZABLE_GLOBAL_H
