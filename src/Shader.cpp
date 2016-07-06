#include "Shader.hpp"

#include <stdexcept>

Shader::Shader(GLenum shaderType)
    : m_shaderId(glCreateShader(shaderType)),
      m_info(nullptr),
      m_compiled(false)
{}

Shader::Shader(GLenum shaderType, char* shaderBody, GLint bodySize/* = 0 */)
    : Shader(shaderType)
{
    setShader(shaderBody, bodySize);
}

Shader::~Shader() {
    glDeleteShader(m_shaderId);
    delete[] m_info;
}

void Shader::setShader(char* shaderBody, GLint bodySize/* = 0 */) {
    m_compiled = false;
    if (bodySize == 0)
        //assumes shaderBody is null-terminated
        glShaderSource(m_shaderId, 1, &shaderBody, 0);
    else
        glShaderSource(m_shaderId, 1, &shaderBody, &bodySize);
}

void Shader::compile() {
    m_compiled = false;

    //try to compile the shader
    glCompileShader(m_shaderId);
    updateInfo();
    GLenum success;
    glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &success);

    //throw exception if something goes wrong
    if (success == GL_FALSE)
        throw std::runtime_error(m_info);

    m_compiled = true;
}

GLenum Shader::getType() const {
    GLenum retVal;
    glGetShaderiv(m_shaderId, GL_SHADER_TYPE, &retVal);
    return retVal;
}

const char* Shader::getInfo() const {
    return m_info;
}

bool Shader::isCompiled() const {
    return m_compiled;
}

Shader::operator GLint() {
    return m_shaderId;
}

void Shader::updateInfo() {
    delete[] m_info;
    GLsizei logLength;
    glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &logLength);
    m_info = new char[logLength];
    glGetShaderInfoLog(m_shaderId, logLength, &logLength, m_info);  
}
