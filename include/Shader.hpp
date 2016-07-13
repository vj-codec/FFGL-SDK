#ifndef NE_SHADER
#define NE_SHADER

#include "FFGLExtensions.hpp"

class Shader {
    public:    
    Shader(GLenum shaderType);
    Shader(GLenum shaderType, const GLcharARB* shaderBody, GLint bodySize = 0);
    ~Shader();

    void setShader(const GLcharARB* shaderBody, GLint bodySize = 0);
    void compile();

    GLint getType() const;
    const GLchar* getInfo() const;
    bool isCompiled() const;
    operator GLhandleARB();

    protected:
    void updateInfo();

    private:
    GLhandleARB m_shaderId;
    GLchar* m_info;
    bool m_compiled;
};

#endif
