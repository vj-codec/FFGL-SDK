#ifndef __PARAMETERS_HPP__
#define __PARAMETERS_HPP__

#include "FFGL.hpp"
#include "ParameterTemplate.hpp"

///
/// \brief A parameter used by a Plugin
///
class Parameter {
    public:
    ///
    /// \brief Constructs the Parameter
    ///
    Parameter();

    ///
    /// \brief Get the value of the Parameter
    ///
    /// \return    The value of the Parameter
    ///
    ParameterValue get();

    ///
    /// \brief Set the value of the Parameter
    ///
    /// \param value    The value
    ///
    void set(ParameterValue value);

    ///
    /// \brief Set the display function used by the Parameter
    ///
    /// \param value    The display function
    ///
    void setDisplay(DisplayFn display);

    ///
    /// \brief Get the value of the Parameter in a format suitable for display
    ///
    /// \return    The display string
    ///
    char* display();

    private:
    ParameterValue m_value;
    DisplayFn m_display;
    char m_buffer[MAX_PARAMETER_DISPLAY_LENGTH];
};

///
/// \brief The parameters used by a Plugin
///
/// Each Plugin instance creates its own set of Parameters from the ParameterTemplate
/// in the PluginManager.
///
class Parameters {
    public:
    ///
    /// \brief Constructs the Parameters
    ///
    /// \param pTemplate    The ParameterTemplate to use
    ///
    Parameters(ParameterTemplate& pTemplate);

    ///
    /// \brief Destroys the Parameters and the contained Parameter array
    ///
    ~Parameters();

    ///
    /// \brief Get a Parameter at the given index
    ///
    /// \param index    The 0-based index of the Parameter
    ///
    /// \return         The Parameter
    ///
    Parameter& operator[](DWORD index);

    private:
    DWORD m_numParameters;
    Parameter* m_parameters;
};

#endif
