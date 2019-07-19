#pragma once
#include <plugin.h>

namespace ad
{
	/**
	 * @brief This enum defines the list of possible categories for the logging information
	 */
	enum LogLevel
	{
		Trace = 0,
		Debug = 1,
		Info = 2,
		Warn = 3,
		Error = 4
	};

	/**
	 * @brief This is the simple interface to interact with the Logger type objects.
	 */
	template <typename string_t, typename map_t>
	class Logger : public Plugin<string_t>
	{
	public:
		/**
		 * @brief Prints the log *message* with the logging category *level*.
		 * @param level the logging category of the log
		 * @param message the log message
		 */
		virtual void log(LogLevel level, string_t const &message) = 0;

		/**
		 * @brief Enable the logger.
		 *
		 * If the logger is disabled, it will not print any log.
		 *
		 * @see disable()
		 */
		virtual void enable() = 0;

		/**
		 * @brief Disable the logger.
		 *
		 * If the logger is disabled, it will not print any log.
		 *
		 * @see enable()
		 */
		virtual void disable() = 0;

		/**
		 * @brief Set the logging level.
		 * 
		 * If called log with log level below specifed, the logging activity will be skipped.
		 * 
		 * @param level the log level
		 * @see logLevel() const
		 * @see log(LogLevel, string_t const &)
		 */
		virtual void setLogLevel(LogLevel level) = 0;

		/**
		 * @brief Set the logger specific ID.
		 * @param id the ID
		 */
		virtual void setId(string_t const &id) = 0;

		/**
		 * @brief Set the logger pattern. 
		 * 
		 * The pattern may contain some keys, that can be set by
		 * #setPatternParam(string_t const &. string_t) function. Those keys are used to print some
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
		 * @param pattern the pattern.
		 * @see setPatternParam(string_t, string_t)
		 */
		virtual void setPattern(string_t const &pattern) = 0;

		/**
		 * @brief Set the logger parameter to be used by the pattern.
		 * @param param_key the parameter key
		 * @param param_val the parameter value
		 */
		virtual void setPatternParam(string_t const &param_key, string_t const &param_val) = 0;

		/**
		 * @brief Get the logger's enabled state.
		 * @return true only and only if the Logger is enabled
		 */
		virtual bool isEnabled() const = 0;

		/**
		 * @brief Get the logging level.
		 * @return the log level of logger
		 * @see setLogLevel(LogLevel)
		 */
		virtual LogLevel logLevel() const = 0;

		/**
		 * @brief Get the logger ID.
		 * @return the logger ID as c_str
		 */
		virtual string_t id() const = 0;

		/**
		 * @brief Get the logger pattern.
		 * @return the logger pattern as c_str
		 */
		virtual string_t pattern() const = 0;

		/**
		 * @brief Get the logger parameter by specified *param_key*.
		 * @param param_key the requested key
		 * @return the value corresponding the key as c_str
		 */
		virtual string_t param(string_t const &param_key) const = 0;

		/**
		 * @brief Get the list of available parameters.
		 * 
		 * The list is null terminating array. Therefore you can iterate it with simple null check
		 * @return the list of registered parameters as null terminating array of c_str.
		 */
		virtual map_t paramList() const = 0;
	};
}
