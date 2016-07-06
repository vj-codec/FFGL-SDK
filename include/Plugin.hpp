#ifndef __PLUGIN_HPP__
#define __PLUGIN_HPP__

#include "PluginCore.hpp"

///
/// \brief The Plugin behavior for this specific FFGLPlugin
///
/// A subclass of the Plugin\Core providing methods that handle graphics
/// processing for this specific FFGLPlugin.
///
class Plugin : public PluginCore {
    public:
    ///
    /// \brief Constructs a Plugin
    ///
    /// \param viewport      The viewport the Plugin should use
    /// \param pTemplate     The template used to create the Plugin's Parameters
    /// \param timeSetter    The function used to set the Plugin's time, if any
    ///
    Plugin(FFGLViewportStruct* viewport, ParameterTemplate& pTemplate, TimeSetter timeSetter);

    ///
    /// \brief The function used by the Plugin to process graphics
    ///
    /// \param data    The graphics information to be processed
    ///
    /// \return FF_SUCCESS or FF_FAIL
    ///
    DWORD processOpenGL(ProcessOpenGLStruct* data);

    private:
};

#endif
