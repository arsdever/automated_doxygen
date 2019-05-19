#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DEOCRATORS_LIB)
#  define DECORATORS_EXPORT Q_DECL_EXPORT
# else
#  define DECORATORS_EXPORT Q_DECL_IMPORT
# endif
#else
# define DECORATORS_EXPORT
#endif
