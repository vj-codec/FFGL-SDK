#include "Info.hpp"

Info::Info()
    : m_info{ 
            API_VERSION_MAJOR, API_VERSION_MINOR,
            "", "", PLUGIN_TYPE 
      },
      m_ext_info{
            PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR,
            const_cast<char*>(PLUGIN_DESCRIPTION), const_cast<char*>(PLUGIN_ABOUT),
            0, nullptr //ExtendedDataBlock not in use
      }
{
    for (DWORD idx = 0; idx < MAX_UID_LENGTH; ++idx)
    {
        m_info.PluginUniqueID[idx] = PLUGIN_UID[idx];
        if (PLUGIN_UID[idx] == 0)
            break;
    }

    for (DWORD idx = 0; idx < MAX_NAME_LENGTH; ++idx)
    {
        m_info.PluginName[idx] = PLUGIN_NAME[idx];
        if (PLUGIN_NAME[idx] == 0)
            break;
    }
}

PluginInfoStruct* Info::getInfo() {
    return &m_info;
}

PluginExtendedInfoStruct* Info::getExtendedInfo() {
    return &m_ext_info;
}

DWORD Info::getPluginCapability(DWORD capability) {
    switch (capability) {
        case FF_CAP_PROCESSOPENGL:
            return FF_SUPPORTED;
        case FF_CAP_MINIMUMINPUTFRAMES:
        case FF_CAP_MAXIMUMINPUTFRAMES:
            return NUM_INPUT_FRAMES;
        case FF_CAP_SETTIME:             // Handled by PluginManager
        case FF_CAP_16BITVIDEO:          // These are always unsupported for GL
        case FF_CAP_24BITVIDEO:
        case FF_CAP_32BITVIDEO:
        case FF_CAP_PROCESSFRAMECOPY:
        case FF_CAP_COPYORINPLACE:
            return FF_UNSUPPORTED;
        default:                         // Don't know capability - assume unsupported
            return FF_UNSUPPORTED;
    }
}
