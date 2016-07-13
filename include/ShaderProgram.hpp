#ifndef NE_SHADERPROGRAM
#define NE_SHADERPROGRAM

#include "FFGLExtensions.hpp"
#include "Shader.hpp"

class ShaderProgram {
    public:
    ShaderProgram();
    ShaderProgram(const GLcharARB* vertShaderBody, const GLcharARB* fragShaderBody);
    ShaderProgram(const GLcharARB* vertShaderBody, const GLcharARB* fragShaderBody, GLint vertBodySize, GLint fragBodySize);
    ~ShaderProgram();

    void setVertShader(const GLcharARB* shaderBody, GLint bodySize = 0);
    void setFragShader(const GLcharARB* shaderBody, GLint bodySize = 0);
    void link();

    void bind();
    void unbind();
    
    bool isLinked() const;
    const GLcharARB* getInfo() const;
    operator GLhandleARB();
    
    protected:
    void updateInfo();

    private:
    GLhandleARB m_programId;
    Shader m_vertShader;
    Shader m_fragShader;
    GLcharARB* m_info;
    bool m_linked;
};

#endif
