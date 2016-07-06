#include "ParameterTemplate.hpp"
#include <cstdio>

#define UNUSED(x) (void)x

char* displayNumericParameter(ParameterValue value, char buffer[MAX_PARAMETER_DISPLAY_LENGTH]) {
    snprintf(buffer, MAX_PARAMETER_DISPLAY_LENGTH + 1, "%5.3f", value.Num);
    return buffer;
}
char* displayStringParameter(ParameterValue value, char buffer[MAX_PARAMETER_DISPLAY_LENGTH]) {
    UNUSED(buffer);
    return value.Str;
}

ParameterTemplate::ParameterTemplate()
    : m_head(nullptr),
      m_tail(nullptr),
      m_numParameters(0)
{}

ParameterTemplate::~ParameterTemplate()
{
    ParameterTemplateNode* node = m_head;
    ParameterTemplateNode* nextNode = nullptr;

    while (node != nullptr)
    {
        nextNode = node->NextNode;
        delete node;
        node = nextNode;
    }
}

inline void ParameterTemplate::addParameterCore(ParameterTemplateNode* node, char name[MAX_PARAMETER_NAME_LENGTH + 1], DWORD type, DisplayFn display) {
    for (DWORD idx = 0; idx < MAX_PARAMETER_NAME_LENGTH; ++idx) {
        node->Name[idx] = name[idx];
        if (name[idx] == 0)
            break;
    }
    node->Type = type;
    node->Display = display;

    if (m_head == nullptr)
        m_head = node;
    else
        m_tail->NextNode = node;
    m_tail = node;

    ++m_numParameters;
}

inline ParameterTemplateNode* ParameterTemplate::getNodeAt(DWORD index) {
    DWORD idx(0);
    ParameterTemplateNode* node(m_head);
    while (node != nullptr && idx < index) {
        ++idx;
        node = node->NextNode;
    }
    return node;
}

void ParameterTemplate::addNumericParameter(char name[MAX_PARAMETER_NAME_LENGTH + 1],
                                            DWORD type, float defaultValue,
                                            DisplayFn display /* = displayNumericParameter */) {
    ParameterTemplateNode* node = new ParameterTemplateNode;
    node->DefaultValue.Num = defaultValue;
    addParameterCore(node, name, type, display);
}

void ParameterTemplate::addTextParameter(char name[MAX_PARAMETER_NAME_LENGTH + 1],
                                         char* defaultValue,
                                         DisplayFn display /* = displayStringParameter */) {
    ParameterTemplateNode* node = new ParameterTemplateNode;
    node->DefaultValue.Str = defaultValue;
    addParameterCore(node, name, FF_TYPE_TEXT, display);
}

ParameterTemplateNode* ParameterTemplate::getHead() {
    return m_head;
}

DWORD ParameterTemplate::getNumParameters() {
    return m_numParameters;
}
char* ParameterTemplate::getParameterName(DWORD index) {
    ParameterTemplateNode* node = getNodeAt(index);
    if (node == nullptr)
        return nullptr;
    else
        return node->Name;
}
DWORD ParameterTemplate::getParameterType(DWORD index) {
    ParameterTemplateNode* node = getNodeAt(index);
    if (node == nullptr)
        return FF_FAIL;
    else
        return node->Type;
}
ParameterValue ParameterTemplate::getParameterDefault(DWORD index) {
    ParameterTemplateNode* node = getNodeAt(index);
    if (node == nullptr)
    {
        ParameterValue ret;
        ret.Data = FF_FAIL;
        return ret;
    }
    else
        return node->DefaultValue;
}
