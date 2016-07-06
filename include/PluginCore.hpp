#ifndef __PLUGINCORE_HPP__
#define __PLUGINCORE_HPP__

#include "FFGL.hpp"
#include "ParameterTemplate.hpp"
#include "Parameters.hpp"

///
/// \brief A pointer to a function that can be used to set a Plugin's time
///
typedef DWORD (*TimeSetter)(double&, double);

///
/// \brief The core of a Plugin
///
/// A PluginCore provides the basic functions and objects required during
/// the lifetime of a Plugin. Most of the provided functions are provided for
/// use by the host, but getViewport is intended to be used by the Plugin
/// itself.
///
class PluginCore {
    public:
    ///
    /// \brief Constructs the PluginCore
    ///
    /// \param viewport      The viewport the Plugin should use
    /// \param pTemplate     The template used to create the Plugin's Parameters
    /// \param timeSetter    The function used to set the Plugin's time, if any
    ///
    PluginCore(FFGLViewportStruct* viewport, ParameterTemplate& pTemplate, TimeSetter timeSetter);

    ///
    /// \brief Gets the current value of a given Parameter
    ///
    /// \param index    The 0-based index of the Parameter
    ///
    /// \return         The current value of the Parameter
    ///
    ParameterValue getParameterValue(DWORD index);

    ///
    /// \brief Sets the current value of a given Parameter
    ///
    /// \param index    The 0-based index of the Parameter
    ///
    /// \return         FF_SUCCESS or FF_FAIL
    ///
    DWORD setParameterValue(DWORD index, ParameterValue value);

    ///
    /// \brief Gets the current value of a given Parameter, formatted for display
    ///
    /// \param index    The 0-based index of the Parameter
    ///
    /// \return         nullptr or a pointer to the display string
    ///
    char* getParameterDisplay(DWORD index);

    ///
    /// \brief Sets the Plugin's time using the Plugin's time setting function
    ///
    /// \param index    The new time
    ///
    /// \return         FF_SUCCESS or FF_FAIL
    ///
    DWORD setTime(double time);

    ///
    /// \brief Get the Plugin's time
    ///
    /// \return    The time
    ///
    double getTime();

    ///
    /// \brief Determines input status (legacy function?)
    ///
    /// \param index    The 0-based input index
    ///
    /// \return         FF_FAIL or FF_IN_USE
    ///
    DWORD getInputStatus(DWORD index);

    protected:

    ///
    /// \brief Get the viewport the Plugin should use
    ///
    /// \return         The viewport
    ///
    const FFGLViewportStruct& getViewport();

    private:
    FFGLViewportStruct m_viewport;
    Parameters m_parameters;
    DWORD m_numParameters;
    TimeSetter m_timeSetter;
    double m_time;
};

#endif
