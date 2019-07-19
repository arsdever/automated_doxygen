#pragma once
namespace ad
{
	template <typename string_t>
	class Plugin;

	/**
	 * @brief This interface provides functionality for dynamic manipulation with plugins
	 * 
	 * It makes possible to load, register preloaded, unregister and unload plugins.
	 */
	template <typename string_t>
	class PluginManager
	{
	public:
		/**
		 * @brief The destructor.
		 */
		virtual ~PluginManager() = default;

		/**
		 * @brief Find a plugin with the specified uuid in managers scope.
		 * @param plugin_uuid the plugin specific uuid
		 * @return the requested plugin with specified uuid
		 */
		virtual Plugin<string_t>* findPlugin(string_t const&plugin_uuid) const = 0;

		/**
		 * @brief Load plugin with specified name.
		 * @param plugin the plugin name
		 * @return the loaded plugin
		 */
		virtual Plugin<string_t>* loadPlugin(string_t const&plugin) = 0;

		/**
		 * @brief Unload the plugin.
		 * @param plugin the plugin name
		 */
		virtual void unloadPlugin(string_t const&plugin) = 0;

		/**
		 * @brief Register already prepared plugin.
		 * @param plugin the plugin
		 */
		virtual void registerPlugin(Plugin<string_t> *plugin) = 0;

		/**
		 * @brief Unregister plugin.
		 * @param plugin the plugin
		 */
		virtual void unregisterPlugin(Plugin<string_t> *plugin) = 0;
	};
}
