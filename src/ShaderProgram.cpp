#include "ShaderProgram.hpp"

#include <stdexcept>

ShaderProgram::ShaderProgram()
    : m_programId(glExt.glCreateProgramObjectARB()),
      m_vertShader(GL_VERTEX_SHADER_ARB),
      m_fragShader(GL_FRAGMENT_SHADER_ARB),
      m_info(nullptr),
      m_linked(false)
{}

ShaderProgram::ShaderProgram(const GLcharARB* vertShaderBody, const GLcharARB* fragShaderBody)
    : m_programId(glExt.glCreateProgramObjectARB()),
      m_vertShader(GL_VERTEX_SHADER_ARB, vertShaderBody),
      m_fragShader(GL_FRAGMENT_SHADER_ARB, fragShaderBody),
      m_info(nullptr),
      m_linked(false)
{}

ShaderProgram::ShaderProgram(const GLcharARB* vertShaderBody, const GLcharARB* fragShaderBody, GLint vertBodySize, GLint fragBodySize)
    : m_programId(glExt.glCreateProgramObjectARB()),
      m_vertShader(GL_VERTEX_SHADER_ARB, vertShaderBody, vertBodySize),
      m_fragShader(GL_FRAGMENT_SHADER_ARB, fragShaderBody, fragBodySize),
      m_info(nullptr),
      m_linked(false)
{}

ShaderProgram::~ShaderProgram() {
    glExt.glDeleteObjectARB(m_programId);
    delete[] m_info;
}

void ShaderProgram::setVertShader(const GLcharARB* shaderBody, GLint bodySize/* = 0 */) {
    m_linked = false;
    m_vertShader.setShader(shaderBody, bodySize);
}

void ShaderProgram::setFragShader(const GLcharARB* shaderBody, GLint bodySize/* = 0 */) {
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
    glExt.glLinkProgramARB(m_programId);
    updateInfo();
    GLint success;
    glExt.glGetObjectParameterivARB(m_programId, GL_OBJECT_LINK_STATUS_ARB, &success);

    //throw exception if something goes wrong
    if (success == 0)
        throw std::runtime_error(m_info);

    m_linked = true;
}

void ShaderProgram::bind() {
    glExt.glUseProgramObjectARB(m_programId);
}

void ShaderProgram::unbind() {
    glExt.glUseProgramObjectARB(0);
}

bool ShaderProgram::isLinked() const {
    return m_linked;
}

const GLcharARB* ShaderProgram::getInfo() const {
    return m_info;
}

ShaderProgram::operator GLhandleARB() {
    return m_programId;
}

void ShaderProgram::updateInfo() {
    delete[] m_info;
    GLint logLength;
    glExt.glGetObjectParameterivARB(m_programId, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength);
    m_info = new char[logLength];
    glExt.glGetInfoLogARB(m_programId, logLength, &logLength, m_info);  
}
