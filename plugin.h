#pragma once
namespace ad
{
	template <typename STRING_TYPE>
	class PluginManager;

	/**
	 * \brief This interface is used to create plugins
	 */
	template <typename STRING_TYPE>
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
		virtual STRING_TYPE uuid() const = 0;

		/**
		 * \brief This function informs the plugin about the plugin manager.
		 * 
		 * The plugin manager might be used in some plugins. It can be set thanks to this function.
		 * 
		 * \param manager the manager
		 */
		virtual void setManager(PluginManager<STRING_TYPE> *manager) = 0;
	};
}
