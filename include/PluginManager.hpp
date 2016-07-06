#ifndef __PLUGINMANAGER_HPP__
#define __PLUGINMANAGER_HPP__

#include "PluginManagerCore.hpp"

///
/// \brief The PluginManager for this specific FFGLPlugin
///
/// A subclass of the PluginManagerCore providing methods that handle
/// setup/cleanup for this specific FFGLPlugin. These include jobs like
/// filling the ParameterTemplate
///
class PluginManager : public PluginManagerCore
{
    public:
    ///
    /// \brief Constructs the PluginManager
    ///
    PluginManager();

    ///
    /// \brief Destroys the PluginManager and all associated Plugins
    ///
    ~PluginManager();

    ///
    /// \brief Handles setup for the PluginManager
    ///
    DWORD initialise();

    ///
    /// \brief Handles cleanup for the PluginManager
    ///
    DWORD deinitialise();

    private:
    bool m_initialised;
};

#endif
