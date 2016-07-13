#include "RenderTexture.hpp"

RenderTexture::RenderTexture(DWORD width, DWORD height)
    : m_Initialized(false),
      m_TexWidth(width),
      m_TexHeight(height),
      m_FBOId(),
      m_TextureId(),
      m_DepthBufferId()
{
    glGenTextures(1, &m_TextureId);
    glExt.glGenRenderbuffersEXT(1, &m_DepthBufferId);
    glExt.glGenFramebuffersEXT(1, &m_FBOId);
}
RenderTexture::~RenderTexture() {
    glDeleteTextures(1, &m_TextureId);
    glExt.glDeleteRenderbuffersEXT(1, &m_DepthBufferId);
    glExt.glDeleteFramebuffersEXT(1, &m_FBOId);
}

void RenderTexture::bind() {
    if (!m_Initialized)
        initializeAndBind();
    else
        glExt.glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_FBOId);
}
void RenderTexture::unbind(GLuint newBindId /* = 0*/) {
    glExt.glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, newBindId);
}

GLuint RenderTexture::getTextureId() const {
    return m_TextureId;
}

void RenderTexture::initializeAndBind()
{
    //texture
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_TexWidth, m_TexHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);

    //depth buffer
    glExt.glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_DepthBufferId);
    glExt.glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT16, m_TexWidth, m_TexHeight);
    glExt.glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

    //fbo
    glExt.glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_FBOId);
    glExt.glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_TextureId, 0);
    glExt.glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_DepthBufferId);

    if (glExt.glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT)
        throw "FBO incomplete after RenderTexture::initializeAndBind";
    else
        m_Initialized = true;
}
