#include "ShaderProgram.hpp"

#include <stdexcept>

ShaderProgram::ShaderProgram()
    : m_programId(glCreateProgram()),
      m_vertShader(GL_VERTEX_SHADER),
      m_fragShader(GL_FRAGMENT_SHADER),
      m_info(nullptr),
      m_linked(false)
{}

ShaderProgram::ShaderProgram(char* vertShaderBody, char* fragShaderBody)
    : m_programId(glCreateProgram()),
      m_vertShader(GL_VERTEX_SHADER, vertShaderBody),
      m_fragShader(GL_FRAGMENT_SHADER, fragShaderBody),
      m_info(nullptr),
      m_linked(false)
{}

ShaderProgram::ShaderProgram(char* vertShaderBody, char* fragShaderBody, GLint vertBodySize, GLint fragBodySize)
    : m_programId(glCreateProgram()),
      m_vertShader(GL_VERTEX_SHADER, vertShaderBody, vertBodySize),
      m_fragShader(GL_FRAGMENT_SHADER, fragShaderBody, fragBodySize),
      m_info(nullptr),
      m_linked(false)
{}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_programId);
    delete[] m_info;
}

void ShaderProgram::setVertShader(char* shaderBody, GLint bodySize/* = 0 */) {
    m_linked = false;
    m_vertShader.setShader(shaderBody, bodySize);
}

void ShaderProgram::setFragShader(char* shaderBody, GLint bodySize/* = 0 */) {
    m_linked = false;
    m_fragShader.setShader(shaderBody, bodySize);
}

void ShaderProgram::link() {
    m_linked = false;

    //make sure both shaders are compiled
    if (!m_vertShader.isCompiled())
        m_vertShader.compile();
    if (!m_fragShader.isCompiled())
        m_fragShader.compile();

    //try to link the program
    glLinkProgram(m_programId);
    updateInfo();
    GLenum success;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &success);

    //throw exception if something goes wrong
    if (success == GL_FALSE)
        throw std::runtime_error(m_info);

    m_linked = true;
}

void ShaderProgram::bind() {
    glUseProgram(m_programId);
}

void ShaderProgram::unbind() {
    glUseProgram(0);
}

bool ShaderProgram::isLinked() const {
    return m_linked;
}

const char* ShaderProgram::getInfo() const {
    return m_info;
}

ShaderProgram::operator GLint() {
    return m_programId;
}

void ShaderProgram::updateInfo() {
    delete[] m_info;
    GLsizei logLength;
    glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
    m_info = new char[logLength];
    glGetProgramInfoLog(m_programId, logLength, &logLength, m_info);  
}
