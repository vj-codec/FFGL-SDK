#include "PluginManagerCore.hpp"

PluginManagerCore::PluginManagerCore()
    : m_head(nullptr),
      m_tail(nullptr),
      m_info(),
      m_parameters(),
      m_timeSetter(nullptr)
{}
PluginManagerCore::~PluginManagerCore()
{
    PluginNode* node = m_head;
    PluginNode* nextNode = nullptr;

    while (node != nullptr)
    {
        nextNode = node->NextNode;
        delete node;
        node = nextNode;
    }
}

Plugin* PluginManagerCore::instantiateGL(FFGLViewportStruct* viewport) {
    Plugin* plugin = new Plugin(viewport, m_parameters, m_timeSetter);
    PluginNode* node = new PluginNode{ plugin, nullptr };

    if (m_head == nullptr)
        m_head = node;
    else
        m_tail->NextNode = node;
    m_tail = node;

    return plugin;
}
DWORD PluginManagerCore::deInstantiateGL(Plugin* plugin) {
    PluginNode* parentNode = nullptr;
    PluginNode* node = m_head;
    while (node != nullptr) {
        if (node->Instance == plugin)
            break;        
        parentNode = node;
        node = node->NextNode;
    }
    
    if (node == nullptr)
        return FF_FAIL;
    else {
        parentNode->NextNode = node->NextNode;
        delete node->Instance;
        delete node;
        return FF_SUCCESS;
    }
}
bool PluginManagerCore::isPlugin(Plugin* plugin) {
    PluginNode* node = m_head;
    while(node != nullptr) {
        if (node->Instance == plugin)
            return true;
    }
    return false;
}

void PluginManagerCore::setTimeSetter(TimeSetter timeSetter) {
    m_timeSetter = timeSetter;
}

PluginInfoStruct* PluginManagerCore::getInfo() { 
    return m_info.getInfo();
}
PluginExtendedInfoStruct* PluginManagerCore::getExtendedInfo() {
    return m_info.getExtendedInfo();
}
DWORD PluginManagerCore::getPluginCapability(DWORD capability) {
    if (capability == FF_CAP_SETTIME)
        return (m_timeSetter == nullptr) ? FF_UNSUPPORTED : FF_SUPPORTED;
    else
        return m_info.getPluginCapability(capability);
}

DWORD PluginManagerCore::getNumParameters() {
    return m_parameters.getNumParameters();
}
char* PluginManagerCore::getParameterName(DWORD index) {
    return m_parameters.getParameterName(index);
}
DWORD PluginManagerCore::getParameterType(DWORD index) {
    return m_parameters.getParameterType(index);
}
ParameterValue PluginManagerCore::getParameterDefault(DWORD index) {
    return m_parameters.getParameterDefault(index);
}
