#pragma once

#include <cstdarg>

namespace ad
{
	/**
	 * \brief This interface is used for an abstraction of instance creation mechanisms.
	 * 
	 * To use it simply derive from and implement the #Factory::getInstance()
	 * pure virtual member function, which constructs an instance specific 
	 * to the given name and the given arguments.
	 * \see LoggerFactory
	 */
	class Factory
	{
	public:
		/**
		 * \brief The destructor.
		 */
		virtual ~Factory() = default;

		/**
		 * \brief This function creates the instance for the given *name* with the given *args*
		 * \param name specifies the instance general identifier
		 * \param args specifies the arguments - needed to instantiate the instance
		 * \return opaque pointer to the requested instance
		 */
		virtual void* getInstance(char const *name, va_list &args) const = 0;
	};
}
