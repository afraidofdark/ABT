#include "stdafx.h"
#include "Material.h"
#include "ABT.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

ABT::Material::Material()
{
  m_color = glm::vec3(1.0f);
}

ABT::Material::Material(std::string file)
{
  m_file = file;
}

ABT::Material::~Material()
{
}

void ABT::Material::Load()
{
  if (m_loaded)
    return;

  rapidxml::file<> file(m_file.c_str());
  rapidxml::xml_document<> doc;
  doc.parse<0>(file.data());

  rapidxml::xml_node<>* rootNode = doc.first_node("material");
  if (rootNode == nullptr)
    return;

  for (rapidxml::xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling())
  {
    if (std::string("diffuseTexture").compare(node->name()) == 0)
    {
      rapidxml::xml_attribute<>* attr = node->first_attribute("name");
      m_diffuseTexture = Main::GetInstance()->m_textureMan.Create(TexturePath(attr->value()));
    }
    else if (std::string("cubeMap").compare(node->name()) == 0)
    {
      rapidxml::xml_attribute<>* attr = node->first_attribute("name");
      m_cubeMap = Main::GetInstance()->m_textureMan.CreateDerived<CubeMap>(TexturePath(attr->value()));
    }
    else if (std::string("shader").compare(node->name()) == 0)
    {
      rapidxml::xml_attribute<>* attr = node->first_attribute("name");
      std::shared_ptr<Shader> shader = Main::GetInstance()->m_shaderMan.Create(ShaderPath(attr->value()));
      if (shader->m_type == GL_VERTEX_SHADER)
      {
        m_vertexShader = shader;
      }
      else if (shader->m_type == GL_FRAGMENT_SHADER)
      {
        m_fragmetShader = shader;
      }
      else
      {
        assert(false);
      }
    }
    else if (std::string("color").compare(node->name()) == 0)
    {
      ExtractXYZFromNode(node, m_color);
    }
    else
    {
      assert(false);
    }
  }

  m_loaded = true;
}

void ABT::Material::Init(bool flushClientSideArray)
{
  if (m_initiated)
    return;

  if (m_diffuseTexture)
  {
    m_diffuseTexture->Init(flushClientSideArray);
    m_renderState.diffuseTexture = m_diffuseTexture->m_textureId;
    m_renderState.diffuseTextureInUse = true;
  }

  if (m_cubeMap)
  {
    m_cubeMap->Init(flushClientSideArray);
    m_renderState.cubeMap = m_cubeMap->m_textureId;
    m_renderState.cubeMapInUse = true;
  }

  if (m_vertexShader)
  {
    m_vertexShader->Init();
  }
  else
  {
    m_vertexShader = Main::GetInstance()->m_shaderMan.Create(ShaderPath("defaultVertex.shader"));
    m_vertexShader->Init();
  }

  if (m_fragmetShader)
  {
    m_fragmetShader->Init();
  }
  else
  {
    m_fragmetShader = Main::GetInstance()->m_shaderMan.Create(ShaderPath("defaultFragment.shader"));
    m_fragmetShader->Init();
  }

  m_initiated = true;
}

ABT::Material* ABT::Material::GetCopy()
{
  return new Material(*this);
}

void ABT::MaterialManager::Init()
{
  ResourceManager::Init();

  Material* material = new Material();
  material->m_vertexShader = Main::GetInstance()->m_shaderMan.Create(ShaderPath("defaultVertex.shader"));
  material->m_fragmetShader = Main::GetInstance()->m_shaderMan.Create(ShaderPath("defaultFragment.shader"));
  material->m_diffuseTexture = Main::GetInstance()->m_textureMan.Create(TexturePath("default.png"));
  material->Init();

  m_storage[MaterialPath("default.material")] = std::shared_ptr<Material> (material);
}
