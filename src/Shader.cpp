#include "Shader.hpp"

#include <stdexcept>

Shader::Shader(GLenum shaderType)
    : m_shaderId(glExt.glCreateShaderObjectARB(shaderType)),
      m_info(nullptr),
      m_compiled(false)
{}

Shader::Shader(GLenum shaderType, const GLcharARB* shaderBody, GLint bodySize/* = 0 */)
    : Shader(shaderType)
{
    setShader(shaderBody, bodySize);
}

Shader::~Shader() {
    glExt.glDeleteObjectARB(m_shaderId);
    delete[] m_info;
}

void Shader::setShader(const GLcharARB* shaderBody, GLint bodySize/* = 0 */) {
    m_compiled = false;
    if (bodySize == 0)
        //assumes shaderBody is null-terminated
        glExt.glShaderSourceARB(m_shaderId, 1, &shaderBody, nullptr);
    else
        glExt.glShaderSourceARB(m_shaderId, 1, &shaderBody, &bodySize);
}

void Shader::compile() {
    m_compiled = false;

    //try to compile the shader
    glExt.glCompileShaderARB(m_shaderId);
    updateInfo();
    GLint success;
    glExt.glGetObjectParameterivARB(m_shaderId, GL_OBJECT_COMPILE_STATUS_ARB, &success);

    //throw exception if something goes wrong
    if (success == 0)
        throw std::runtime_error(m_info);

    m_compiled = true;
}

GLint Shader::getType() const {
    GLint retVal;
    glExt.glGetObjectParameterivARB(m_shaderId, GL_OBJECT_SUBTYPE_ARB, &retVal);
    return retVal;
}

const GLchar* Shader::getInfo() const {
    return m_info;
}

bool Shader::isCompiled() const {
    return m_compiled;
}

Shader::operator GLhandleARB() {
    return m_shaderId;
}

void Shader::updateInfo() {
    delete[] m_info;
    GLsizei logLength;
    glExt.glGetObjectParameterivARB(m_shaderId, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength);
    m_info = new char[logLength];
    glExt.glGetInfoLogARB(m_shaderId, logLength, &logLength, m_info);  
}
