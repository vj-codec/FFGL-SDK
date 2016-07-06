#include "PluginCore.hpp"
#include "Config.hpp"

PluginCore::PluginCore(FFGLViewportStruct* viewport, ParameterTemplate& pTemplate, TimeSetter timeSetter)
    : m_viewport(*viewport),
      m_parameters(pTemplate),
      m_numParameters(pTemplate.getNumParameters()),
      m_timeSetter(timeSetter),
      m_time(0.0)
{}

ParameterValue PluginCore::getParameterValue(DWORD index) {
    if (index >= m_numParameters) {
        ParameterValue ret;
        ret.Data = FF_FAIL;
        return ret;
    }
    else
        return m_parameters[index].get();
}

DWORD PluginCore::setParameterValue(DWORD index, ParameterValue value) {
    if (index >= m_numParameters) {
        return FF_FAIL;
    }
    else {
        m_parameters[index].set(value);
        return FF_SUCCESS;
    }
}

char* PluginCore::getParameterDisplay(DWORD index) {
    if (index >= m_numParameters) {
        return nullptr;
    } 
    else {
        return m_parameters[index].display();
    }
}

DWORD PluginCore::setTime(double time) {
    if (m_timeSetter == nullptr)
        return FF_FAIL;
    else
        return m_timeSetter(m_time, time);
}

double PluginCore::getTime() {
    return m_time;
}

DWORD PluginCore::getInputStatus(DWORD dwIndex)
{
    if (dwIndex >= NUM_INPUT_FRAMES)
        return FF_FAIL;
    else
        return FF_INPUT_INUSE;
}
