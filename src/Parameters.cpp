#include "Parameters.hpp"

Parameter::Parameter()
    : m_value(),
      m_display(nullptr),
      m_buffer{}
{}

ParameterValue Parameter::get() {
    return m_value;
}

void Parameter::set(ParameterValue value) {
    m_value = value;
}

void Parameter::setDisplay(DisplayFn display) {
    m_display = display;
}

char* Parameter::display() {
    return m_display(m_value, m_buffer);
}

Parameters::Parameters(ParameterTemplate& pTemplate)
    : m_numParameters(pTemplate.getNumParameters()),
      m_parameters(nullptr)
{
    m_parameters = new Parameter[m_numParameters];
    ParameterTemplateNode* parameter = pTemplate.getHead();
    DWORD idx = 0;
    while (parameter != nullptr)
    {
        m_parameters[idx].set(parameter->DefaultValue);
        m_parameters[idx].setDisplay(parameter->Display);
        ++idx;
        parameter = parameter->NextNode;
    }
}

Parameters::~Parameters() {
    delete[] m_parameters;
}

Parameter& Parameters::operator[](DWORD index) {    
    return m_parameters[index];
}

