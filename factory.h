#pragma once
#include <cstdarg>

#define EXTERN_C_GETTER(__factory_class, __factory_return_interface, __dllname) \
extern "C" __dllname##_EXPORT __factory_return_interface* getInstance(char const* a, ...) \
{ \
	va_list l; \
	va_start(l, a); \
	__factory_return_interface *r = static_cast<__factory_return_interface*>(__factory_class().getInstance(a, l)); \
	va_end(l); \
	return r; \
}

namespace ad
{
	/**
	 * @brief This interface is used for an abstraction of instance creation mechanisms.
	 * 
	 * To use it simply derive from and implement the #Factory::getInstance()
	 * pure virtual member function, which constructs an instance from specified type
	 */
	class Factory
	{
	public:
		/**
		 * @brief The destructor.
		 */
		virtual ~Factory() = default;

		/**
		 * @brief This function creates the instance for the given type
		 * @param type specifies the instance general identifier
		 * @return opaque pointer to the requested instance
		 */
		virtual void* getInstance(int type) const = 0;
	};
}
