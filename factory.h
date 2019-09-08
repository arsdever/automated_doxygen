#pragma once

namespace ad
{
	/**
	 * @brief This interface is used for an abstraction of instance creation mechanisms.
	 * 
	 * To use it simply derive from and implement the #Factory::getInstance()
	 * pure virtual member function, which constructs an instance from specified type
	 */
	template <typename BYTEBUF_TYPE>
	class Factory
	{
	public:
		typedef BYTEBUF_TYPE bytebuf_t;

	public:
		/**
		 * @brief The destructor.
		 */
		virtual ~Factory() = default;

		/**
		 * @brief Get instance for specified configuration.
		 * @param type specifies the instance general identifier
		 * @return opaque pointer to the requested instance
		 */
		virtual void* getInstance() const = 0;

		/**
		 * @brief Configure the factory.
		 * 
		 * It is very usefull when trying to get some particlar type of instance from the bunch of available types.
		 * It parses the specified configuration string into usefull options and uses them in future actions.
		 * 
		 * @param configuration the configuration string
		 * @see configureWithFile
		 */
		virtual void configure(bytebuf_t const &configuration) = 0;

		/**
		 * @brief Configure the factory using configuration file
		 * 
		 * This function is very likely to the function @a{configure()}, but it uses a path to the config file
		 * and reads all the configuration from that file.
		 * 
		 * @param path_to_config_file the path to the configuration file
		 * @see configure
		 */
		virtual void configureWithFile(bytebuf_t const &path_to_config_file) = 0;
	};
}
