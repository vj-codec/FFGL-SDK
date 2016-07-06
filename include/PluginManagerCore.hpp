#ifndef __PLUGINMANAGERCORE_HPP__
#define __PLUGINMANAGERCORE_HPP__

#include "FFGL.hpp"
#include "Info.hpp"
#include "ParameterTemplate.hpp"
#include "Plugin.hpp"

///
/// \brief A pointer to a function that can be used to set a Plugin's time
///
typedef DWORD (*TimeSetter)(double&, double);
class Plugin;

///
/// \brief A node in a linked list of Plugin instances
///
struct PluginNode {
    Plugin* Instance;
    PluginNode* NextNode;
};

///
/// \brief The core of the PluginManager
///
/// A PluginManagerCore provides the basic functions and objects required
/// for plugin management. In addition to managing Plugin instantiation and
/// deinstantiation a PluginManagerCore contains functions providing useful
/// information about the plugin and the ParameterTemplate during the
/// creation of Plugin instances
///
class PluginManagerCore
{
    public:
    ///
    /// \brief Constructs the PluginManagerCore
    ///
    PluginManagerCore();

    ///
    /// \brief Destroys the PluginManagerCore and all associated Plugins
    ///
    ~PluginManagerCore();

    ///
    /// \brief Creates a new Plugin and adds it to the list of managed Plugin 
    /// instances
    ///
    /// \param viewport    Viewport information to be passed to the new Plugin
    ///
    /// \return           A pointer to the new Plugin
    ///
    Plugin* instantiateGL(FFGLViewportStruct* viewport);

    ///
    /// \brief Destroys the given plugin if it managed by the PluginManagerCore
    ///
    /// \param plugin    The Plugin to be destroyed
    ///
    /// \return         FF_SUCCESS if the Plugin was destroyed, FF_FAIL otherwise
    ///
    DWORD deInstantiateGL(Plugin* plugin);

    ///
    /// \brief Determines whether the given plugin is managed by the PluginManagerCore
    ///
    /// \param plugin    The Plugin to check
    ///
    /// \return         true if this PluginManagerCore manages the Plugin,
    ///                  false otherwise
    ///
    bool isPlugin(Plugin* plugin);

    ///
    /// \brief Defines a function to set the time member of a Plugin based on
    ///        an input value
    ///
    /// The signature if the function is DWORD(double&, double). The inputs will be 
    /// Plugin.m_time and the host's input time respectively. The function should 
    /// return FF_SUCCESS or FF_FAIL
    ///
    /// \param timeSetter    The function to be used
    ///
    void setTimeSetter(TimeSetter timeSetter);

    ///
    /// \brief Get useful information about the FFGLPlugin
    ///
    /// Returns information about the FFGL version, plugin name, plugin type,
    /// and a unique plugin identifier
    ///
    /// \return Information about the plugin
    ///
    PluginInfoStruct* getInfo();

    ///
    /// \brief Get useful information about the FFGLPlugin not given by 
    /// PluginManagerCore::getInfo
    ///
    /// Returns information about the plugin version, plugin description, and plugin 
    /// "about" text
    ///
    /// \return Extra information about the plugin
    ///
    PluginExtendedInfoStruct* getExtendedInfo();

    ///
    /// \brief Get information about the FFGLPlugin's supported capablities	
    ///
    /// \param capability    The capability of interest; one of the FF_CAP_... 
    /// constexprs
    ///
    /// \return Whether/how the capability is supported. Usually FF_SUPPORTED or 
    /// FF_UNSUPPORTED
    ///
    DWORD getPluginCapability(DWORD capability);

    ///
    /// \brief Gets the number of parameters in the PluginManagerCore's
    /// ParameterTemplate
    ///
    /// \return The number of parameters in the template
    ///
    DWORD getNumParameters();

    ///
    /// \brief Gets the name of a parameter in the PluginManagerCore's 
    /// ParameterTemplate
    ///
    /// \param index The 0-based index of the parameter
    ///
    /// \return The name of the specified parameter
    ///
    char* getParameterName(DWORD index);

    ///
    /// \brief Gets the type of a parameter in the PluginManagerCore's 
    /// ParameterTemplate
    ///
    /// \param index The 0-based index of the parameter
    ///
    /// \return The type of the specified parameter
    ///
    DWORD getParameterType(DWORD index);

    ///
    /// \brief Gets the default value of a parameter in the PluginManagerCore's
    /// ParameterTemplate
    ///
    /// \param index The 0-based index of the parameter
    ///
    /// \return The type of the specified parameter
    ///
    ParameterValue getParameterDefault(DWORD index);

    private:
    PluginNode* m_head;
    PluginNode* m_tail;
    Info m_info;
    TimeSetter m_timeSetter;

    protected:
    ParameterTemplate parameters; ///< The parameter template
};

#endif
