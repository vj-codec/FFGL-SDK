#include "Plugin.hpp"

Plugin::Plugin(FFGLViewportStruct* viewport, ParameterTemplate& pTemplate, TimeSetter timeSetter)
    : PluginCore(viewport, pTemplate, timeSetter)
{}

DWORD Plugin::processOpenGL(ProcessOpenGLStruct* data) {
    (void)data;
    return FF_SUCCESS;
}
