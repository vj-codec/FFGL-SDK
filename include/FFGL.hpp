////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FFGL.hpp
//
// FreeFrame is an open-source cross-platform real-time video effects plugin system.
// It provides a framework for developing video effects plugins and hosts on Windows, 
// Linux and Mac OSX. 
// 
// Copyright (c) 2006 www.freeframe.org
// All rights reserved. 
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// First version, Marcus Clements (marcus@freeframe.org) 
// www.freeframe.org
//
// FreeFrame 1.0 upgrade by Pete Warden
// www.petewarden.com
//
// FreeFrame 1.0 - 03 upgrade by Gualtiero Volpe
// Gualtiero.Volpe@poste.it
//
// #ifdef tweaks for FreeFrameGL upgrade by Trey Harrison
// www.harrisondigitalmedia.com
//
// FFGL.h by Trey Harrison
// www.harrisondigitalmedia.com
// 
// FreeFrame.h and FFGL.h merged and tweaked by Nate Eizenga
// eizengan@gmail.com
// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Redistribution and use in source and binary forms, with or without modification, 
//	are permitted provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in
//    the documentation and/or other materials provided with the
//    distribution.
//  * Neither the name of FreeFrame nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
//	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
//	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
//	IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
//	INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
//	BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
//	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
//	OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
//	OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
//	OF THE POSSIBILITY OF SUCH DAMAGE. 
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __FFGL_HPP__
#define __FFGL_HPP__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
    #include <windows.h>
    #include <gl/gl.h>
#elif defined TARGET_OS_MAC
    #define GL_GLEXT_LEGACY
    #include <OpenGL/gl.h>

    extern "C" {
#elif defined __linux__
    #include <GL/gl.h>

    extern "C" {
#else
    #error set includes for your OS
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FreeFrame Types
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Typedefs for Linux and MacOS - in Windows these are defined in files included by windows.h
#if defined(__linux__) || defined(TARGET_OS_MAC)
    typedef unsigned int DWORD;
    typedef unsigned char BYTE;
    typedef void *LPVOID;
#endif

// PluginInfoStruct
typedef struct PluginInfoStructTag {
    DWORD    APIMajorVersion;
    DWORD    APIMinorVersion;
    BYTE    PluginUniqueID[4];  // 4 chars uniqueID - not null terminated
    BYTE    PluginName[16];     // 16 chars plugin friendly name - not null terminated
    DWORD    PluginType;        // Effect or source
} PluginInfoStruct;

// PluginExtendedInfoStruct   
typedef struct PluginExtendedInfoStructTag {
    DWORD PluginMajorVersion;
    DWORD PluginMinorVersion;
    char* Description;
    char* About;
    DWORD FreeFrameExtendedDataSize;
    void* FreeFrameExtendedDataBlock;
} PluginExtendedInfoStruct;

// VideoInfoStruct
typedef struct VideoInfoStructTag {
    DWORD FrameWidth;   // width of frame in pixels
    DWORD FrameHeight;  // height of frame in pixels
    DWORD BitDepth;     // enumerated indicator of bit depth of video: 0 = 16 bit 5-6-5   1 = 24bit packed   2 = 32bit
    DWORD Orientation;            
} VideoInfoStruct;

// ProcessFrameCopyStruct
typedef struct ProcessFrameCopyStructTag {
    DWORD numInputFrames;
    void** ppInputFrames;
    void* pOutputFrame;
} ProcessFrameCopyStruct;

// SetParameterStruct
typedef struct SetParameterStructTag {
    DWORD ParameterNumber;
    DWORD NewParameterValue;
} SetParameterStruct;

// plugMain function return values
typedef union plugMainUnionTag {
    DWORD ivalue;
    float fvalue;
    VideoInfoStruct* VISvalue;
    PluginInfoStruct* PISvalue;
    char* svalue;
} plugMainUnion;

//FFGLViewportStruct (for InstantiateGL)
typedef struct FFGLViewportStructTag
{
  GLuint x,y,width,height;
} FFGLViewportStruct;

//FFGLTextureStruct (for ProcessOpenGLStruct)
typedef struct FFGLTextureStructTag
{
  DWORD Width, Height;
  DWORD HardwareWidth, HardwareHeight;
  GLuint Handle; //the actual texture handle, from glGenTextures()
} FFGLTextureStruct;

// ProcessOpenGLStruct
typedef struct ProcessOpenGLStructTag {
  DWORD numInputTextures;
  FFGLTextureStruct **inputTextures;
  
  //if the host calls ProcessOpenGL with a framebuffer object actively bound
  //(as is the case when the host is capturing the plugins output to an offscreen texture)
  //the host must provide the GL handle to its EXT_framebuffer_object
  //so that the plugin can restore that binding if the plugin
  //makes use of its own FBO's for intermediate rendering
  GLuint HostFBO; 
} ProcessOpenGLStruct;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FreeFrame defines
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Function codes
constexpr DWORD FF_GETINFO = 0;
constexpr DWORD FF_INITIALISE = 1;
constexpr DWORD FF_DEINITIALISE = 2;
constexpr DWORD FF_PROCESSFRAME = 3;
constexpr DWORD FF_GETNUMPARAMETERS = 4;
constexpr DWORD FF_GETPARAMETERNAME = 5;
constexpr DWORD FF_GETPARAMETERDEFAULT = 6;
constexpr DWORD FF_GETPARAMETERDISPLAY = 7;
constexpr DWORD FF_SETPARAMETER = 8;
constexpr DWORD FF_GETPARAMETER = 9;
constexpr DWORD FF_GETPLUGINCAPS = 10;
constexpr DWORD FF_INSTANTIATE = 11;
constexpr DWORD FF_DEINSTANTIATE = 12;
constexpr DWORD FF_GETEXTENDEDINFO = 13;
constexpr DWORD FF_PROCESSFRAMECOPY = 14;
constexpr DWORD FF_GETPARAMETERTYPE = 15;
constexpr DWORD FF_GETINPUTSTATUS = 16;
constexpr DWORD FF_PROCESSOPENGL = 17;
constexpr DWORD FF_INSTANTIATEGL = 18;
constexpr DWORD FF_DEINSTANTIATEGL = 19;
constexpr DWORD FF_SETTIME = 20;

// Return values
constexpr DWORD FF_SUCCESS = 0;
constexpr DWORD FF_FAIL = 0xFFFFFFFF;
constexpr DWORD FF_TRUE = 1;
constexpr DWORD FF_FALSE = 0;
constexpr DWORD FF_SUPPORTED = 1;
constexpr DWORD FF_UNSUPPORTED = 0;

// Plugin types
constexpr DWORD FF_EFFECT = 0;
constexpr DWORD FF_SOURCE = 1;

// Plugin capabilities
constexpr DWORD FF_CAP_16BITVIDEO = 0;
constexpr DWORD FF_CAP_24BITVIDEO = 1;
constexpr DWORD FF_CAP_32BITVIDEO = 2;
constexpr DWORD FF_CAP_PROCESSFRAMECOPY = 3;
constexpr DWORD FF_CAP_PROCESSOPENGL = 4;
constexpr DWORD FF_CAP_SETTIME = 5;
constexpr DWORD FF_CAP_MINIMUMINPUTFRAMES = 10;
constexpr DWORD FF_CAP_MAXIMUMINPUTFRAMES = 11;
constexpr DWORD FF_CAP_COPYORINPLACE = 15;

// Plugin optimization
constexpr DWORD FF_CAP_PREFER_NONE = 0;
constexpr DWORD FF_CAP_PREFER_INPLACE = 1;
constexpr DWORD FF_CAP_PREFER_COPY = 2;
constexpr DWORD FF_CAP_PREFER_BOTH = 3;

// Parameter types
constexpr DWORD FF_TYPE_BOOLEAN = 0; 
constexpr DWORD FF_TYPE_EVENT = 1;
constexpr DWORD FF_TYPE_RED = 2; 
constexpr DWORD FF_TYPE_GREEN = 3;
constexpr DWORD FF_TYPE_BLUE = 4;
constexpr DWORD FF_TYPE_XPOS = 5;
constexpr DWORD FF_TYPE_YPOS = 6;
constexpr DWORD FF_TYPE_STANDARD = 10;
constexpr DWORD FF_TYPE_ALPHA = 11;
constexpr DWORD FF_TYPE_TEXT = 100;

// Input status
constexpr DWORD FF_INPUT_NOTINUSE = 0;
constexpr DWORD FF_INPUT_INUSE = 1;

// Image depth
constexpr DWORD FF_DEPTH_16 = 0;
constexpr DWORD FF_DEPTH_24 = 1;
constexpr DWORD FF_DEPTH_32 = 2;

// Image orientation
constexpr DWORD FF_ORIENTATION_TL = 1;
constexpr DWORD FF_ORIENTATION_BL = 2;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function prototypes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// plugMain - The one and only exposed function
// parameters: 
//    functionCode - tells the plugin which function is being called
//  pParam - 32-bit parameter or 32-bit pointer to parameter structure
//
// PLUGIN DEVELOPERS:  you shouldn't need to change this function
//
// All parameters are cast as 32-bit untyped pointers and cast to appropriate
// types here
// 
// All return values are cast to 32-bit untyped pointers here before return to 
// the host
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
    BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
    __declspec(dllexport) plugMainUnion __stdcall plugMain(DWORD functionCode, DWORD inputValue, DWORD instanceID);
    typedef __declspec(dllimport) plugMainUnion (__stdcall *FF_Main_FuncPtr)(DWORD, DWORD, DWORD);
#elif defined(__linux__) || defined(TARGET_OS_MAC)
    plugMainUnion plugMain(DWORD functionCode, DWORD inputValue, DWORD instanceID);
    typedef plugMainUnion (*FF_Main_FuncPtr)(DWORD funcCode, DWORD inputVal, DWORD instanceID);
#else
    #error modify function signature for your OS
#endif

#if defined(__linux__) || defined(TARGET_OS_MAC)
    } // extern "C"
#endif

#endif // __FFGL_HPP__
