#include "PluginManager.hpp"
#include <iostream>

PluginManager::PluginManager()
    : PluginManagerCore(),
      m_initialised(false)
{}

DWORD PluginManager::initialise() {
    if (m_initialised)
        return FF_SUCCESS;

    //do setup here
    std::cout << "initialised" << std::endl;

    m_initialised = true;
    return FF_SUCCESS;
}
DWORD PluginManager::deinitialise() {
    if (!m_initialised)
        return FF_SUCCESS;

    //do cleanup here
    std::cout << "deinitialised" << std::endl;

    m_initialised = false;
    return FF_SUCCESS;
}
