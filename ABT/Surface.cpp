#include "stdafx.h"
#include "Surface.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Node.h"

ABT::Surface::Surface(std::shared_ptr<Texture> texture, glm::vec2 pivotOffset)
{
  m_mesh->m_material->m_diffuseTexture = texture;
  m_pivotOffset = pivotOffset;
  CreateQuat();
  m_loaded = true;
}

ABT::Surface::Surface(std::shared_ptr<Texture> texture, const std::vector<Vertex>& vertices)
{
  m_mesh->m_material->m_diffuseTexture = texture;
  m_mesh->m_clientSideVertices = vertices;
  m_loaded = true;
}

ABT::Surface::Surface(std::string file, glm::vec2 pivotOffset)
{
  m_file = file;
  m_pivotOffset = pivotOffset;
}

ABT::Surface::~Surface()
{
}

ABT::EntityType ABT::Surface::GetType()
{
  return EntityType::Entity_Surface;
}

void ABT::Surface::Load()
{
  if (m_loaded)
    return;

  assert(!m_file.empty());
  m_mesh->m_material->m_diffuseTexture = Main::GetInstance()->m_textureMan.Create(m_file);
  CreateQuat();

  m_loaded = true;
}

void ABT::Surface::Init(bool flushClientSideArray)
{
  if (m_initiated)
    return;

  m_mesh->m_material->m_diffuseTexture->Init(flushClientSideArray);
  m_mesh->Init(flushClientSideArray);

  m_mesh->m_material->m_renderState.blendFunction = ABT::BlendFunction::SRC_ALPHA_ONE_MINUS_SRC_ALPHA;
  m_mesh->m_material->m_renderState.depthTestEnabled = false;

  m_initiated = true;
}

void ABT::Surface::CreateQuat()
{
  float width = (float)m_mesh->m_material->m_diffuseTexture->m_width;
  float height = (float)m_mesh->m_material->m_diffuseTexture->m_height;
  float depth = 0;
  glm::vec2 absOffset = glm::vec2(m_pivotOffset.x * width, m_pivotOffset.y * height);

  std::vector<ABT::Vertex> vertices;
  vertices.resize(6);
  vertices[0].pos = glm::vec3(-absOffset.x, -absOffset.y, depth);
  vertices[0].tex = glm::vec2(0.0f, 1.0f);
  vertices[1].pos = glm::vec3(width - absOffset.x, -absOffset.y, depth);
  vertices[1].tex = glm::vec2(1.0f, 1.0f);
  vertices[2].pos = glm::vec3(-absOffset.x, height - absOffset.y, depth);
  vertices[2].tex = glm::vec2(0.0f, 0.0f);

  vertices[3].pos = glm::vec3(width - absOffset.x, -absOffset.y, depth);
  vertices[3].tex = glm::vec2(1.0f, 1.0f);
  vertices[4].pos = glm::vec3(width - absOffset.x, height - absOffset.y, depth);
  vertices[4].tex = glm::vec2(1.0f, 0.0f);
  vertices[5].pos = glm::vec3(-absOffset.x, height - absOffset.y, depth);
  vertices[5].tex = glm::vec2(0.0f, 0.0f);

  m_mesh->m_clientSideVertices = vertices;
}
