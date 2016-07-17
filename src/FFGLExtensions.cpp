#include "FFGLExtensions.hpp"
#include <cstring>

FFGLExtensions glExt;

FFGLExtensions::FFGLExtensions()
{
    initialize();
}

void FFGLExtensions::initialize() {
    #ifdef _WIN32
        initWGLEXTSwapControl();
    #endif

    initMultitexture();
    initARBShaderObjects();
    initEXTFramebufferObject();
}

void* FFGLExtensions::getProcAddress(const char* name) {
    #ifdef _WIN32
        void* result = wglGetProcAddress(name);
        if (result != nullptr)
            return result;
    #elif defined TARGET_OS_MAC
        // Prepend a '_' for the Unix C symbol mangling convention
        int symbolLength = strlen(name) + 2; //1 for the _, another for the trailing null
        char symbolName[1024];
        if (symbolLength > sizeof(symbolName)) {
            //symbol name too long;
            throw "symbol name too long";
            return nullptr;
        }
        symbolName[0] = '_';
        strcpy(symbolName + 1, name);
        NSSymbol symbol = nullptr;

        if (NSIsSymbolNameDefined(symbolName))
            symbol = NSLookupAndBindSymbol(symbolName);

        if (symbol != nullptr) {
            return NSAddressOfSymbol(symbol);
        }
    #elif defined __linux__
        void* result = (void*)glXGetProcAddress((const GLubyte*)name);
        if (result != nullptr)
            return result;
    #else
        #error Define this for your OS  
    #endif
    throw "getProcAddress found no address";//this will be caught by one of the Init() functions below
    return nullptr;    
}

void FFGLExtensions::initMultitexture() {
    try {
        glActiveTexture = (glActiveTexturePROC)(getProcAddress("glActiveTexture"));
        glClientActiveTexture = (glClientActiveTexturePROC)(getProcAddress("glClientActiveTexture"));
        glMultiTexCoord1d = (glMultiTexCoord1dPROC)(getProcAddress("glMultiTexCoord1d"));
        glMultiTexCoord1dv = (glMultiTexCoord1dvPROC)(getProcAddress("glMultiTexCoord1dv"));
        glMultiTexCoord1f = (glMultiTexCoord1fPROC)(getProcAddress("glMultiTexCoord1f"));
        glMultiTexCoord1fv = (glMultiTexCoord1fvPROC)(getProcAddress("glMultiTexCoord1fv"));
        glMultiTexCoord1i = (glMultiTexCoord1iPROC)(getProcAddress("glMultiTexCoord1i"));
        glMultiTexCoord1iv = (glMultiTexCoord1ivPROC)(getProcAddress("glMultiTexCoord1iv"));
        glMultiTexCoord1s = (glMultiTexCoord1sPROC)(getProcAddress("glMultiTexCoord1s"));
        glMultiTexCoord1sv = (glMultiTexCoord1svPROC)(getProcAddress("glMultiTexCoord1sv"));
        glMultiTexCoord2d = (glMultiTexCoord2dPROC)(getProcAddress("glMultiTexCoord2d"));
        glMultiTexCoord2dv = (glMultiTexCoord2dvPROC)(getProcAddress("glMultiTexCoord2dv"));
        glMultiTexCoord2f = (glMultiTexCoord2fPROC)(getProcAddress("glMultiTexCoord2f"));
        glMultiTexCoord2fv = (glMultiTexCoord2fvPROC)(getProcAddress("glMultiTexCoord2fv"));
        glMultiTexCoord2i = (glMultiTexCoord2iPROC)(getProcAddress("glMultiTexCoord2i"));
        glMultiTexCoord2iv = (glMultiTexCoord2ivPROC)(getProcAddress("glMultiTexCoord2iv"));
        glMultiTexCoord2s = (glMultiTexCoord2sPROC)(getProcAddress("glMultiTexCoord2s"));
        glMultiTexCoord2sv = (glMultiTexCoord2svPROC)(getProcAddress("glMultiTexCoord2sv"));
        glMultiTexCoord3d = (glMultiTexCoord3dPROC)(getProcAddress("glMultiTexCoord3d"));
        glMultiTexCoord3dv = (glMultiTexCoord3dvPROC)(getProcAddress("glMultiTexCoord3dv"));
        glMultiTexCoord3f = (glMultiTexCoord3fPROC)(getProcAddress("glMultiTexCoord3f"));
        glMultiTexCoord3fv = (glMultiTexCoord3fvPROC)(getProcAddress("glMultiTexCoord3fv"));
        glMultiTexCoord3i = (glMultiTexCoord3iPROC)(getProcAddress("glMultiTexCoord3i"));
        glMultiTexCoord3iv = (glMultiTexCoord3ivPROC)(getProcAddress("glMultiTexCoord3iv"));
        glMultiTexCoord3s = (glMultiTexCoord3sPROC)(getProcAddress("glMultiTexCoord3s"));
        glMultiTexCoord3sv = (glMultiTexCoord3svPROC)(getProcAddress("glMultiTexCoord3sv"));
        glMultiTexCoord4d = (glMultiTexCoord4dPROC)(getProcAddress("glMultiTexCoord4d"));
        glMultiTexCoord4dv = (glMultiTexCoord4dvPROC)(getProcAddress("glMultiTexCoord4dv"));
        glMultiTexCoord4f = (glMultiTexCoord4fPROC)(getProcAddress("glMultiTexCoord4f"));
        glMultiTexCoord4fv = (glMultiTexCoord4fvPROC)(getProcAddress("glMultiTexCoord4fv"));
        glMultiTexCoord4i = (glMultiTexCoord4iPROC)(getProcAddress("glMultiTexCoord4i"));
        glMultiTexCoord4iv = (glMultiTexCoord4ivPROC)(getProcAddress("glMultiTexCoord4iv"));
        glMultiTexCoord4s = (glMultiTexCoord4sPROC)(getProcAddress("glMultiTexCoord4s"));
        glMultiTexCoord4sv = (glMultiTexCoord4svPROC)(getProcAddress("glMultiTexCoord4sv"));
    }
    catch(...) {
        m_MultitextureLoaded = false;
        return;
    }
    m_MultitextureLoaded = true;
}
void FFGLExtensions::initARBShaderObjects() {
    try {
        glDeleteObjectARB = (glDeleteObjectARBPROC)(getProcAddress("glDeleteObjectARB"));
        glGetHandleARB = (glGetHandleARBPROC)(getProcAddress("glGetHandleARB"));
        glDetachObjectARB = (glDetachObjectARBPROC)(getProcAddress("glDetachObjectARB"));
        glCreateShaderObjectARB = (glCreateShaderObjectARBPROC)(getProcAddress("glCreateShaderObjectARB"));
        glShaderSourceARB = (glShaderSourceARBPROC)(getProcAddress("glShaderSourceARB"));
        glCompileShaderARB = (glCompileShaderARBPROC)(getProcAddress("glCompileShaderARB"));
        glCreateProgramObjectARB = (glCreateProgramObjectARBPROC)(getProcAddress("glCreateProgramObjectARB"));
        glAttachObjectARB = (glAttachObjectARBPROC)(getProcAddress("glAttachObjectARB"));
        glLinkProgramARB = (glLinkProgramARBPROC)(getProcAddress("glLinkProgramARB"));
        glUseProgramObjectARB = (glUseProgramObjectARBPROC)(getProcAddress("glUseProgramObjectARB"));
        glValidateProgramARB = (glValidateProgramARBPROC)(getProcAddress("glValidateProgramARB"));
        glUniform1fARB = (glUniform1fARBPROC)(getProcAddress("glUniform1fARB"));
        glUniform2fARB = (glUniform2fARBPROC)(getProcAddress("glUniform2fARB"));
        glUniform3fARB = (glUniform3fARBPROC)(getProcAddress("glUniform3fARB"));
        glUniform4fARB = (glUniform4fARBPROC)(getProcAddress("glUniform4fARB"));
        glUniform1iARB = (glUniform1iARBPROC)(getProcAddress("glUniform1iARB"));
        glUniform2iARB = (glUniform2iARBPROC)(getProcAddress("glUniform2iARB"));
        glUniform3iARB = (glUniform3iARBPROC)(getProcAddress("glUniform3iARB"));
        glUniform4iARB = (glUniform4iARBPROC)(getProcAddress("glUniform4iARB"));
        glUniform1fvARB = (glUniform1fvARBPROC)(getProcAddress("glUniform1fvARB"));
        glUniform2fvARB = (glUniform2fvARBPROC)(getProcAddress("glUniform2fvARB"));
        glUniform3fvARB = (glUniform3fvARBPROC)(getProcAddress("glUniform3fvARB"));
        glUniform4fvARB = (glUniform4fvARBPROC)(getProcAddress("glUniform4fvARB"));
        glUniform1ivARB = (glUniform1ivARBPROC)(getProcAddress("glUniform1ivARB"));
        glUniform2ivARB = (glUniform2ivARBPROC)(getProcAddress("glUniform2ivARB"));
        glUniform3ivARB = (glUniform3ivARBPROC)(getProcAddress("glUniform3ivARB"));
        glUniform4ivARB = (glUniform4ivARBPROC)(getProcAddress("glUniform4ivARB"));
        glUniformMatrix2fvARB = (glUniformMatrix2fvARBPROC)(getProcAddress("glUniformMatrix2fvARB"));
        glUniformMatrix3fvARB = (glUniformMatrix3fvARBPROC)(getProcAddress("glUniformMatrix3fvARB"));
        glUniformMatrix4fvARB = (glUniformMatrix4fvARBPROC)(getProcAddress("glUniformMatrix4fvARB"));
        glGetObjectParameterfvARB = (glGetObjectParameterfvARBPROC)(getProcAddress("glGetObjectParameterfvARB"));
        glGetObjectParameterivARB = (glGetObjectParameterivARBPROC)(getProcAddress("glGetObjectParameterivARB"));
        glGetInfoLogARB = (glGetInfoLogARBPROC)(getProcAddress("glGetInfoLogARB"));
        glGetAttachedObjectsARB = (glGetAttachedObjectsARBPROC)(getProcAddress("glGetAttachedObjectsARB"));
        glGetUniformLocationARB = (glGetUniformLocationARBPROC)(getProcAddress("glGetUniformLocationARB"));
        glGetActiveUniformARB = (glGetActiveUniformARBPROC)(getProcAddress("glGetActiveUniformARB"));
        glGetUniformfvARB = (glGetUniformfvARBPROC)(getProcAddress("glGetUniformfvARB"));
        glGetUniformivARB = (glGetUniformivARBPROC)(getProcAddress("glGetUniformivARB"));
        glGetShaderSourceARB = (glGetShaderSourceARBPROC)(getProcAddress("glGetShaderSourceARB"));
    }
    catch(...) {
        m_ARB_shader_objectsLoaded = false;
        return;
    }
    m_ARB_shader_objectsLoaded = true;
}
void FFGLExtensions::initEXTFramebufferObject() {
    try {
        glBindFramebufferEXT = (glBindFramebufferEXTPROC)(getProcAddress("glBindFramebufferEXT"));
        glBindRenderbufferEXT = (glBindRenderbufferEXTPROC)(getProcAddress("glBindRenderbufferEXT"));
        glCheckFramebufferStatusEXT = (glCheckFramebufferStatusEXTPROC)(getProcAddress("glCheckFramebufferStatusEXT"));
        glDeleteFramebuffersEXT = (glDeleteFramebuffersEXTPROC)(getProcAddress("glDeleteFramebuffersEXT"));
        glDeleteRenderbuffersEXT = (glDeleteRenderbuffersEXTPROC)(getProcAddress("glDeleteRenderbuffersEXT"));
        glFramebufferRenderbufferEXT = (glFramebufferRenderbufferEXTPROC)(getProcAddress("glFramebufferRenderbufferEXT"));
        glFramebufferTexture1DEXT = (glFramebufferTexture1DEXTPROC)(getProcAddress("glFramebufferTexture1DEXT"));
        glFramebufferTexture2DEXT = (glFramebufferTexture2DEXTPROC)(getProcAddress("glFramebufferTexture2DEXT"));
        glFramebufferTexture3DEXT = (glFramebufferTexture3DEXTPROC)(getProcAddress("glFramebufferTexture3DEXT"));
        glGenFramebuffersEXT = (glGenFramebuffersEXTPROC)(getProcAddress("glGenFramebuffersEXT"));
        glGenRenderbuffersEXT = (glGenRenderbuffersEXTPROC)(getProcAddress("glGenRenderbuffersEXT"));
        glGenerateMipmapEXT = (glGenerateMipmapEXTPROC)(getProcAddress("glGenerateMipmapEXT"));
        glGetFramebufferAttachmentParameterivEXT = (glGetFramebufferAttachmentParameterivEXTPROC)(getProcAddress("glGetFramebufferAttachmentParameterivEXT"));
        glGetRenderbufferParameterivEXT = (glGetRenderbufferParameterivEXTPROC)(getProcAddress("glGetRenderbufferParameterivEXT"));
        glIsFramebufferEXT = (glIsFramebufferEXTPROC)(getProcAddress("glIsFramebufferEXT"));
        glIsRenderbufferEXT = (glIsRenderbufferEXTPROC)(getProcAddress("glIsRenderbufferEXT"));
        glRenderbufferStorageEXT = (glRenderbufferStorageEXTPROC)(getProcAddress("glRenderbufferStorageEXT"));
    }
    catch(...) {
        m_EXT_framebuffer_objectLoaded = false;
        return;
    }
    m_EXT_framebuffer_objectLoaded = true;
}

#ifdef _WIN32  
    void FFGLExtensions::initWGLEXTSwapControl() {
        try {
            wglSwapIntervalEXT = (wglSwapIntervalEXTPROC)(getProcAddress("wglSwapIntervalEXT"));
            wglGetSwapIntervalEXT = (wglGetSwapIntervalEXTPROC)(getProcAddress("wglGetSwapIntervalEXT"));
        }
        catch(...) {
            m_WGL_EXT_swap_controlLoaded = false;
            return;
        }
        m_WGL_EXT_swap_controlLoaded = true;
    }
#endif
