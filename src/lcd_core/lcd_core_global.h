#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LCD_CORE_LIB)
#  define LCD_CORE_EXPORT Q_DECL_EXPORT
# else
#  define LCD_CORE_EXPORT Q_DECL_IMPORT
# endif
#else
# define LCD_CORE_EXPORT
#endif
