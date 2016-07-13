#ifndef NE_RENDERTEXTURE
#define NE_RENDERTEXTURE

#include "FFGLExtensions.hpp"

class RenderTexture {
    public:
    RenderTexture(DWORD width, DWORD height);
    ~RenderTexture();

    void bind();
    void unbind(GLuint newBindId = 0);

    GLuint getTextureId() const;

    private:
    void initializeAndBind();

    bool m_Initialized;
    DWORD m_TexWidth;
    DWORD m_TexHeight;
    GLuint m_FBOId;
    GLuint m_TextureId;
    GLuint m_DepthBufferId;
};

#endif
