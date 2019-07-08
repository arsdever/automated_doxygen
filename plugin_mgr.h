#pragma once
namespace ad
{
	template <typename STRING_TYPE>
	class Plugin;

	/**
	 * \brief This interface provides functionality for dynamic manipulation with plugins
	 * 
	 * It makes possible to load, register preloaded, unregister and unload plugins.
	 */
	template <typename STRING_TYPE>
	class PluginManager
	{
	public:
		/**
		 * \brief The destructor.
		 */
		virtual ~PluginManager() = default;

		/**
		 * \brief Find a plugin with the specified uuid in managers scope.
		 * \param plugin_uuid the plugin specific uuid
		 * \return the requested plugin with specified uuid
		 */
		virtual Plugin<STRING_TYPE>* findPlugin(STRING_TYPE const&plugin_uuid) const = 0;

		/**
		 * \brief Load plugin with specified name.
		 * \param plugin the plugin name
		 * \return the loaded plugin
		 */
		virtual Plugin<STRING_TYPE>* loadPlugin(STRING_TYPE const&plugin) = 0;

		/**
		 * \brief Unload the plugin.
		 * \param plugin the plugin name
		 */
		virtual void unloadPlugin(STRING_TYPE const&plugin) = 0;

		/**
		 * \brief Register already prepared plugin.
		 * \param plugin the plugin
		 */
		virtual void registerPlugin(Plugin<STRING_TYPE> *plugin) = 0;

		/**
		 * \brief Unregister plugin.
		 * \param plugin the plugin
		 */
		virtual void unregisterPlugin(Plugin<STRING_TYPE> *plugin) = 0;
	};
}
