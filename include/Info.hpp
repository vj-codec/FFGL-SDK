#ifndef __INFO_HPP__
#define __INFO_HPP__

#include "FFGL.hpp"
#include "Config.hpp"

///
/// \brief Contains information about the FFGLPlugin
///
/// A simple container for Plugin info mainly comprised of data in Config.hpp.
/// Returns data in a format expected by the host.
///
class Info final {
    public:
    ///
    /// \brief Constructs the plugin info
    ///
    Info();

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
    /// \brief Get useful information about the FFGLPlugin not given by getInfo
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

    private:
    PluginInfoStruct m_info;
    PluginExtendedInfoStruct m_ext_info;
};

#endif // __INFO_HPP__
