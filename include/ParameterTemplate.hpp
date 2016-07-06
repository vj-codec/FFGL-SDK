#ifndef __PARAMETERTEMPLATE_HPP__
#define __PARAMETERTEMPLATE_HPP__

#include "FFGL.hpp"

///
/// \brief The longest allowed length of a string used to name a parameter
///
constexpr DWORD MAX_PARAMETER_NAME_LENGTH = 16;

///
/// \brief The longest allowed length of a string used to display a parameter value
///
constexpr DWORD MAX_PARAMETER_DISPLAY_LENGTH = 16;

///
/// \brief A union used to pass parameter values simply
///
typedef union ParameterValueType {
    DWORD Data; ///< Generic data - usually a pointer
    float Num;  ///< Numerical data
    char* Str;  ///< Pointer to a string
} ParameterValue;


///
/// \brief A function that places a display string in the provided buffer and
/// returns it
///
typedef char* (*DisplayFn)(ParameterValue value, char buffer[MAX_PARAMETER_DISPLAY_LENGTH]);

///
/// \brief A node in the linked list of ParameterTemplates
///
struct ParameterTemplateNode {
    char Name[MAX_PARAMETER_NAME_LENGTH];
    DWORD Type;
    ParameterValue DefaultValue;
    DisplayFn Display;
    ParameterTemplateNode* NextNode;
};

///
/// \brief The default display function for numeric Parameters
///
char* displayNumericParameter(ParameterValue value, char buffer[MAX_PARAMETER_DISPLAY_LENGTH]);

///
/// \brief The default display function for string Parameters
///
char* displayStringParameter(ParameterValue value, char buffer[MAX_PARAMETER_DISPLAY_LENGTH]);

///
/// \brief A template used to create the Parameters in a new Plugin instance
///
/// A ParameterTemplate manages a list of ParameterTemplateNodes which is used
/// to instantiate new Plugins. A ParameterTemplateNode determines a Parameter's
/// name, type, default value, and a function used to display the Parameter's
/// current value.
///
class ParameterTemplate {
    public:
    ///
    /// \brief Constructs the ParameterTemplate
    ///
    ParameterTemplate();

    ///
    /// \brief Destroys the ParameterTemplate and all associated ParameterTemplateNodes
    ///
    ~ParameterTemplate();

    ///
    /// \brief Add a numeric parameter to the ParameterTemplate
    ///
    /// \param name            The name of the Parameter
    /// \param type            The underlying type of the Parameter - one of the 
    ///                        FF_TYPE_... constexprs. FF_TYPE_TEXT should be added 
    ///                        with addTextParameter.
    /// \param defaultValue    The default value of the parameter. Must be in 0...1.
    /// \param display         Optional. A function used to retrieve the value in a
    ///                        format suitable for display. A default is provided.
    ///
    void addNumericParameter(char name[MAX_PARAMETER_NAME_LENGTH + 1],
                             DWORD type, float defaultValue,
                             DisplayFn display = displayNumericParameter);

    ///
    /// \brief Add a text parameter to the ParameterTemplate
    ///
    /// \param name            The name of the Parameter
    /// \param defaultValue    The default value of the parameter. Must be null-terminated.
    /// \param display         Optional. A function used to retrieve the value in a
    ///                        format suitable for display. A default is provided.
    ///
    void addTextParameter(char name[MAX_PARAMETER_NAME_LENGTH + 1],
                          char* defaultValue,
                          DisplayFn display = displayStringParameter);
    ///
    /// \brief Get the first ParameterTemplateNode in the linked list
    ///
    ParameterTemplateNode* getHead();


    ///
    /// \brief Gets the number of parameters in the ParameterTemplate
    ///
    /// \return The number of parameters in the template
    ///
    DWORD getNumParameters();

    ///
    /// \brief Gets the name of a parameter in the ParameterTemplate
    ///
    /// \param index The 0-based index of the parameter
    ///
    /// \return The name of the specified parameter
    ///
    char* getParameterName(DWORD index);

    ///
    /// \brief Gets the type of a parameter in the ParameterTemplate
    ///
    /// \param index The 0-based index of the parameter
    ///
    /// \return The type of the specified parameter
    ///
    DWORD getParameterType(DWORD index);

    ///
    /// \brief Gets the default value of a parameter in the ParameterTemplate
    ///
    /// \param index The 0-based index of the parameter
    ///
    /// \return The type of the specified parameter
    ///
    ParameterValue getParameterDefault(DWORD index);

    private:
    inline void addParameterCore(ParameterTemplateNode* node, char name[MAX_PARAMETER_NAME_LENGTH + 1], DWORD type, DisplayFn display);
    inline ParameterTemplateNode* getNodeAt(DWORD index);
    ParameterTemplateNode* m_head;
    ParameterTemplateNode* m_tail;
    DWORD m_numParameters;
};

#endif
