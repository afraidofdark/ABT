#include "stdafx.h"
#include "Texture.h"
#include "lodepng.h"

ABT::Texture::Texture()
{
}

ABT::Texture::Texture(std::string file)
{
  m_file = file;
}

ABT::Texture::~Texture()
{
  glDeleteTextures(1, &m_textureId);
}

void ABT::Texture::Load()
{
  if (m_loaded)
    return;

  if (!lodepng::decode(m_image, m_width, m_height, m_file))
    m_loaded = true;
}

void ABT::Texture::Init(bool flushClientSideArray)
{
  if (m_initiated)
    return;

  if (m_image.size() <= 0 || m_width <= 0 || m_height <= 0)
    return;

  glGenTextures(1, &m_textureId);
  glBindTexture(GL_TEXTURE_2D, m_textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.data());
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  if (flushClientSideArray)
    m_image.clear();
  m_initiated = true;
}

ABT::CubeMap::CubeMap()
{
}

ABT::CubeMap::CubeMap(std::string file)
  : Texture(file)
{
}

ABT::CubeMap::~CubeMap()
{
}

void ABT::CubeMap::Load()
{
  if (m_loaded)
    return;

  m_images.resize(6);
  size_t pos = m_file.find("px.png");
  if (pos == std::string::npos)
  {
    Logger::GetInstance()->Log("Inapropriate postfix. Looking for \"px.png\": " + m_file);
    return;
  }

  std::string file = m_file.substr(0, pos);

  for (int i = 0; i < 6; i++)
  {
    std::string postfix = "px.png";
    switch (i)
    {
    case 1:
      postfix = "nx.png";
      break;
    case 2:
      postfix = "py.png";
      break;
    case 3:
      postfix = "ny.png";
      break;
    case 4:
      postfix = "pz.png";
      break;
    case 5:
      postfix = "nz.png";
      break;
    }

    if (lodepng::decode(m_images[i], m_width, m_height, file + postfix))
    {
      Logger::GetInstance()->Log("Missing file: " + file + postfix);
      Logger::GetInstance()->Log("Cube map loading requires additional 5 png files with postfix \"nx py ny pz nz\".");
      m_loaded = false;
      
      m_images.clear();
      return;
    }
  }

  m_loaded = true;
}

void ABT::CubeMap::Init(bool flushClientSideArray)
{
  if (m_initiated)
    return;

  if (!m_loaded)
    return;

  // Sanity check.
  if (m_images[0].size() <= 0 || m_width <= 0 || m_height <= 0)
    return;

  glGenTextures(1, &m_textureId);
  glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureId);

  unsigned int sides[6] =
  {
    GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
  };

  for (int i = 0; i < 6; i++)
  {
    glTexImage2D(sides[i], 0, GL_RGBA, m_width, m_width, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_images[i].data());
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  if (flushClientSideArray)
    m_image.clear();
  m_initiated = true;
}
