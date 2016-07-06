#include "PluginManager.hpp"
#include <iostream>

PluginInfoStruct* getInfo() {
    DWORD infoPtr = plugMain(FF_GETINFO, 0, 0).ivalue;
    return reinterpret_cast<PluginInfoStruct*>(infoPtr);
}


PluginExtendedInfoStruct* getExtendedInfo() {
    DWORD infoPtr = plugMain(FF_GETEXTENDEDINFO, 0, 0).ivalue;
    return reinterpret_cast<PluginExtendedInfoStruct*>(infoPtr);
}

void printInfo() {
    std::cout << "FFGL v" << getInfo()->APIMajorVersion << "." << getInfo()->APIMinorVersion << std::endl;
    for (DWORD idx = 0; idx < MAX_NAME_LENGTH; ++idx)
        std::cout << getInfo()->PluginName[idx];
    std::cout << "(";
    for (DWORD idx = 0; idx < MAX_UID_LENGTH; ++idx)
        std::cout << getInfo()->PluginUniqueID[idx];
    std::cout << ") - ";
    switch (getInfo()->PluginType) {
        case FF_EFFECT:
            std::cout << "Effect";
            break;
        case FF_SOURCE: 
            std::cout << "Source";
            break;
    }
}

void printExtendedInfo() {
    std::cout << " v" <<  getExtendedInfo()->PluginMajorVersion << "." << getExtendedInfo()->PluginMinorVersion << std::endl;
    std::cout << getExtendedInfo()->Description << std::endl;
    std::cout << getExtendedInfo()->About << std::endl;
}

void printCapabilities() {
    std::cout << "FF_CAP_16BITVIDEO: " << ((plugMain(FF_GETPLUGINCAPS, FF_CAP_16BITVIDEO, 0).ivalue == FF_SUPPORTED) ? "Supported" : "Unsupported") << std::endl;
    std::cout << "FF_CAP_24BITVIDEO: " << ((plugMain(FF_GETPLUGINCAPS, FF_CAP_24BITVIDEO, 0).ivalue == FF_SUPPORTED) ? "Supported" : "Unsupported") << std::endl;
    std::cout << "FF_CAP_32BITVIDEO: " << ((plugMain(FF_GETPLUGINCAPS, FF_CAP_32BITVIDEO, 0).ivalue == FF_SUPPORTED) ? "Supported" : "Unsupported") << std::endl;
    std::cout << "FF_CAP_PROCESSFRAMECOPY: " << ((plugMain(FF_GETPLUGINCAPS, FF_CAP_PROCESSFRAMECOPY, 0).ivalue == FF_SUPPORTED) ? "Supported" : "Unsupported") << std::endl;
    std::cout << "FF_CAP_PROCESSOPENGL: " << ((plugMain(FF_GETPLUGINCAPS, FF_CAP_PROCESSOPENGL, 0).ivalue == FF_SUPPORTED) ? "Supported" : "Unsupported") << std::endl;
    std::cout << "FF_CAP_SETTIME: " << ((plugMain(FF_GETPLUGINCAPS, FF_CAP_SETTIME, 0).ivalue == FF_SUPPORTED) ? "Supported" : "Unsupported") << std::endl;
    std::cout << "FF_CAP_MINIMUMINPUTFRAMES: " << plugMain(FF_GETPLUGINCAPS, FF_CAP_MINIMUMINPUTFRAMES, 0).ivalue << std::endl;
    std::cout << "FF_CAP_MAXIMUMINPUTFRAMES: " << plugMain(FF_GETPLUGINCAPS, FF_CAP_MINIMUMINPUTFRAMES, 0).ivalue << std::endl;
    std::cout << "FF_CAP_COPYORINPLACE: " << ((plugMain(FF_GETPLUGINCAPS, FF_CAP_COPYORINPLACE, 0).ivalue == FF_SUPPORTED) ? "Supported" : "Unsupported") << std::endl;
}



int main() {
    std::cout << "Initialising: ";
    plugMain(FF_INITIALISE, 0, 0);
    printInfo();
    printExtendedInfo();
    printCapabilities();
    std::cout << "Deinitialising: ";
    plugMain(FF_DEINITIALISE, 0, 0);

    return 0;
}
