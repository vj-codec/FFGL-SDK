#ifndef NE_SHADER
#define NE_SHADER

#ifdef _WIN32
    #include <gl/gl.h>
#elif defined TARGET_OS_MAC
    #include <OpenGL/gl.h>
#elif defined __linux__
    #include <GL/gl.h>
#else
    #error set includes for your OS
#endif

#include <string>

class Shader {
    public:    
    Shader(GLenum shaderType);
    Shader(GLenum shaderType, char* shaderBody, GLint bodySize = 0);
    ~Shader();

    void setShader(char* shaderBody, GLint bodySize = 0);
    void compile();

    GLenum getType() const;
    const char* getInfo() const;
    bool isCompiled() const;
    operator GLint();

    protected:
    void updateInfo();

    private:
    GLuint m_shaderId;
    GLchar* m_info;
    bool m_compiled;
};

#endif
