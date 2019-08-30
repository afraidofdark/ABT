#pragma once

#include "Resource.h"
#include "ResourceManager.h"
#include "GL\glew.h"
#include <vector>

namespace ABT
{

  class Texture : public Resource
  {
  public:
    Texture();
    Texture(std::string file);
    virtual ~Texture();

    virtual void Load();
    virtual void Init(bool flushClientSideArray = true);

  public:
    GLuint m_textureId = 0;
    unsigned int m_width = 0;
    unsigned int m_height = 0;
    std::vector<unsigned char> m_image;
  };

  class CubeMap : public Texture
  {
  public:
    CubeMap();
    CubeMap(std::string file);
    ~CubeMap();

    void Load();
    void Init(bool flushClientSideArray = true);

  public:
    std::vector<std::vector<unsigned char>> m_images;
  };

  class TextureManager : public ResourceManager<Texture>
  {
  };

}