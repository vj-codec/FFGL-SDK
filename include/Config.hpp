#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include "FFGL.hpp"

///
/// \brief The maximum length of the unique identifier used by the FFGLPlugin. DO NOT CHANGE.
///
constexpr DWORD MAX_UID_LENGTH = 4;
///
/// \brief The maximum length of the name used by the FFGLPlugin. DO NOT CHANGE.
///
constexpr DWORD MAX_NAME_LENGTH = 16;


///
/// \brief The FFGL major version
///
constexpr DWORD API_VERSION_MAJOR = 1;

///
/// \brief The FFGL minor version in ### format (e.g. 500 for 1.5)
///
constexpr DWORD API_VERSION_MINOR = 500;

///
/// \brief The unique identifier for the FFGLPlugin
///
constexpr BYTE PLUGIN_UID[MAX_UID_LENGTH + 1] = "ABCD";

///
/// \brief The name of the FFGLPlugin
///
constexpr BYTE PLUGIN_NAME[MAX_NAME_LENGTH + 1] = "My Plugin";

///
/// \brief A description of the FFGLPlugin
///
constexpr char PLUGIN_DESCRIPTION[] = "This is a plugin that does some stuff";

///
/// \brief FFGLPlugin "about" information
///
constexpr char PLUGIN_ABOUT[] = "I made this plugin";

///
/// \brief The FFGLPlugin major version
///
constexpr DWORD PLUGIN_VERSION_MAJOR = 1;

///
/// \brief The FFGLPlugin minor version in ### format (e.g. 500 for 1.5)
///
constexpr DWORD PLUGIN_VERSION_MINOR = 000;

///
/// \brief The type of the FFGLPlugin (FF_EFFECT or FF_SOURCE)
///
constexpr DWORD PLUGIN_TYPE = FF_EFFECT;

///
/// \brief The number of frames expected by the FFGLPlugin during graphics processing
///
constexpr DWORD NUM_INPUT_FRAMES = 1;

#endif
