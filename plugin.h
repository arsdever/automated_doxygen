#pragma once
namespace ad
{
	/**
	 * \brief This interface is used to create plugins
	 */
	class Plugin
	{
	public:
		/**
		 * \brief The destructor.
		 */
		virtual ~Plugin() = default;

		/**
		 * \brief This function is to identify the plugin
		 * \return the plugin Uuid
		 */
		virtual char const* uuid() const = 0;
	};
}
