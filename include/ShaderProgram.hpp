#ifndef NE_SHADERPROGRAM
#define NE_SHADERPROGRAM

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
#include "Shader.hpp"

class ShaderProgram {
    public:
    ShaderProgram();
    ShaderProgram(char* vertShaderBody, char* fragShaderBody);
    ShaderProgram(char* vertShaderBody, char* fragShaderBody, GLint vertBodySize, GLint fragBodySize);
    ~ShaderProgram();

    void setVertShader(char* shaderBody, GLint bodySize = 0);
    void setFragShader(char* shaderBody, GLint bodySize = 0);
    void link();

    void bind();
    void unbind();
    
    bool isLinked() const;
    const char* getInfo() const;
    operator GLint();
    
    protected:
    void updateInfo();

    private:
    GLint m_programId;
    Shader m_vertShader;
    Shader m_fragShader;
    GLchar* m_info;
    bool m_linked;
};

#endif
