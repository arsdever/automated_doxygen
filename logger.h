#ifndef LOGGER_H
#define LOGGER_H

#include <plugin.h>

namespace ad
{
	/**
	 * \brief This is the simple interface to interact with the Logger type objects.
	 */
	class Logger : public Plugin
	{
	public:
		/**
		 * \brief This enum defines the list of possible categories for the logging information
		 */
		enum LogLevel
		{
			Trace = 0,
			Debug = 1,
			Info = 2,
			Warn = 3,
			Error = 4
		};

	public:
		/**
		 * \brief Prints the log *message* with the logging category *level*.
		 * \param level the logging category of the log
		 * \param message the log message
		 */
		virtual void log(LogLevel level, char const *message) const = 0;

		/**
		 * \brief Set the logger specific ID.
		 * \param id the ID
		 */
		virtual void setId(char const *id) = 0;

		/**
		 * \brief Set the logger pattern. 
		 * 
		 * The pattern may contain some keys, that can be set by
		 * #setPatternParam(char const *. char const*) function. Those keys are used to print some
		 * useful information (such as thread id, date/time, logger id, etc.) with the message.
		 * Identification of the keys and the set of predefined keys must be provided by the implementer.
		 * ```
		 * Logger* logger = getLogger(); // suppose the getLogger function has been already implemented
		 * logger->setPattern("[%now][%thd] [%lvl] (%param): %m"); // set the logging pattern
		 * logger->setPatternParam("param", "my_param_string"); // set the **param**
		 * logger->log(Logger::LogLevel::Error, "Some error message"); // log some message
		 * ```
		 * The result must be something like the following (if the other keys are predefined as well)
		 * > [01.02.1970 01:23:45:678][Thread 12345] [ ERROR ] (my_param_string): Some error message
		 * 
		 * \param pattern the pattern.
		 * \see setPatternParam(char const*, char const*)
		 */
		virtual void setPattern(char const *pattern) = 0;

		/**
		 * \brief Set the logger parameter to be used by the pattern.
		 * \param param_key the parameter key
		 * \param param_val the parameter value
		 */
		virtual void setPatternParam(char const *param_key, char const *param_val) = 0;

		/**
		 * \brief Get the logger ID.
		 * \return the logger ID as c_str
		 */
		virtual char const* id() const = 0;

		/**
		 * \brief Get the logger pattern.
		 * \return the logger pattern as c_str
		 */
		virtual char const* pattern() const = 0;

		/**
		 * \brief Get the logger parameter by specified *param_key*.
		 * \param param_key the requested key
		 * \return the value corresponding the key as c_str
		 */
		virtual char const* param(char const *param_key) const = 0;

		/**
		 * \brief Get the list of available parameters.
		 * 
		 * The list is null terminating array. Therefore you can iterate it with simple null check
		 * \return the list of registered parameters as null terminating array of c_str.
		 */
		virtual char const** paramList() const = 0;
	};
}

#endif
