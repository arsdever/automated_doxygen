#pragma once
namespace ad
{
	template <typename string_t>
	class PluginManager;

	/**
	 * @brief This interface is used to create plugins
	 */
	template <typename string_t>
	class Plugin
	{
	public:
		/**
		 * @brief The destructor.
		 */
		virtual ~Plugin() = default;

		/**
		 * @brief This function is to identify the plugin
		 * @return the plugin Uuid
		 */
		virtual string_t uuid() const = 0;

		/**
		 * @brief This function informs the plugin about the plugin manager.
		 * 
		 * The plugin manager might be used in some plugins. It can be set thanks to this function.
		 * 
		 * @param manager the manager
		 */
		virtual void setManager(PluginManager<string_t> *manager) = 0;

		/**
		 * @brief This is a slot and it must be called whenever a new plugin was loaded by the PluginManager.
		 * 
		 * @param plugin the newly loaded plugin
		 */
		virtual void onPluginLoaded(Plugin<string_t> *plugin) = 0;
	};
}
