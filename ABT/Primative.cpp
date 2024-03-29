#include "stdafx.h"
#include "Primative.h"
#include "Mesh.h"
#include "ABT.h"
#include "MathUtil.h"

ABT::Cube::Cube()
{
  std::vector<ABT::Vertex> vertices;
  vertices.resize(36);

  // Front
  vertices[0].pos = glm::vec3(-0.5f, 0.5f, 0.5f);
  vertices[0].tex = glm::vec2(0.0f, 1.0f);
  vertices[1].pos = glm::vec3(-0.5f, -0.5f, 0.5f);
  vertices[1].tex = glm::vec2(0.0f, 0.0f);
  vertices[2].pos = glm::vec3(0.5f, -0.5f, 0.5f);
  vertices[2].tex = glm::vec2(1.0f, 0.0f);

  vertices[3].pos = glm::vec3(-0.5f, 0.5f, 0.5f);
  vertices[3].tex = glm::vec2(0.0f, 1.0f);
  vertices[4].pos = glm::vec3(0.5f, -0.5f, 0.5f);
  vertices[4].tex = glm::vec2(1.0f, 0.0f);
  vertices[5].pos = glm::vec3(0.5f, 0.5f, 0.5f);
  vertices[5].tex = glm::vec2(1.0f, 1.0f);

  // Right
  vertices[6].pos = glm::vec3(0.5f, 0.5f, 0.5f);
  vertices[6].tex = glm::vec2(0.0f, 1.0f);
  vertices[7].pos = glm::vec3(0.5f, -0.5f, 0.5f);
  vertices[7].tex = glm::vec2(0.0f, 0.0f);
  vertices[8].pos = glm::vec3(0.5f, -0.5f, -0.5f);
  vertices[8].tex = glm::vec2(1.0f, 0.0f);

  vertices[9].pos = glm::vec3(0.5f, 0.5f, 0.5f);
  vertices[9].tex = glm::vec2(0.0f, 1.0f);
  vertices[10].pos = glm::vec3(0.5f, -0.5f, -0.5f);
  vertices[10].tex = glm::vec2(1.0f, 0.0f);
  vertices[11].pos = glm::vec3(0.5f, 0.5f, -0.5f);
  vertices[11].tex = glm::vec2(1.0f, 1.0f);

  // Top
  vertices[12].pos = glm::vec3(-0.5f, 0.5f, 0.5f);
  vertices[12].tex = glm::vec2(0.0f, 0.0f);
  vertices[13].pos = glm::vec3(0.5f, 0.5f, 0.5f);
  vertices[13].tex = glm::vec2(1.0f, 0.0f);
  vertices[14].pos = glm::vec3(0.5f, 0.5f, -0.5f);
  vertices[14].tex = glm::vec2(1.0f, 1.0f);

  vertices[15].pos = glm::vec3(-0.5f, 0.5f, 0.5f);
  vertices[15].tex = glm::vec2(0.0f, 0.0f);
  vertices[16].pos = glm::vec3(0.5f, 0.5f, -0.5f);
  vertices[16].tex = glm::vec2(1.0f, 1.0f);
  vertices[17].pos = glm::vec3(-0.5f, 0.5f, -0.5f);
  vertices[17].tex = glm::vec2(0.0f, 1.0f);

  // Back
  vertices[18].pos = glm::vec3(-0.5f, 0.5f, -0.5f);
  vertices[18].tex = glm::vec2(0.0f, 1.0f);
  vertices[19].pos = glm::vec3(0.5f, -0.5f, -0.5f);
  vertices[19].tex = glm::vec2(1.0f, 0.0f);
  vertices[20].pos = glm::vec3(-0.5f, -0.5f, -0.5f);
  vertices[20].tex = glm::vec2(0.0f, 0.0f);

  vertices[21].pos = glm::vec3(-0.5f, 0.5f, -0.5f);
  vertices[21].tex = glm::vec2(0.0f, 1.0f);
  vertices[22].pos = glm::vec3(0.5f, 0.5f, -0.5f);
  vertices[22].tex = glm::vec2(1.0f, 1.0f);
  vertices[23].pos = glm::vec3(0.5f, -0.5f, -0.5f);
  vertices[23].tex = glm::vec2(1.0f, 0.0f);

  // Left
  vertices[24].pos = glm::vec3(-0.5f, 0.5f, 0.5f);
  vertices[24].tex = glm::vec2(0.0f, 1.0f);
  vertices[25].pos = glm::vec3(-0.5f, -0.5f, -0.5f);
  vertices[25].tex = glm::vec2(1.0f, 0.0f);
  vertices[26].pos = glm::vec3(-0.5f, -0.5f, 0.5f);
  vertices[26].tex = glm::vec2(0.0f, 0.0f);

  vertices[27].pos = glm::vec3(-0.5f, 0.5f, 0.5f);
  vertices[27].tex = glm::vec2(0.0f, 1.0f);
  vertices[28].pos = glm::vec3(-0.5f, 0.5f, -0.5f);
  vertices[28].tex = glm::vec2(1.0f, 1.0f);
  vertices[29].pos = glm::vec3(-0.5f, -0.5f, -0.5f);
  vertices[29].tex = glm::vec2(1.0f, 0.0f);

  // Bottom
  vertices[30].pos = glm::vec3(-0.5f, -0.5f, 0.5f);
  vertices[30].tex = glm::vec2(0.0f, 1.0f);
  vertices[31].pos = glm::vec3(0.5f, -0.5f, -0.5f);
  vertices[31].tex = glm::vec2(1.0f, 0.0f);
  vertices[32].pos = glm::vec3(0.5f, -0.5f, 0.5f);
  vertices[32].tex = glm::vec2(0.0f, 0.0f);

  vertices[33].pos = glm::vec3(-0.5f, -0.5f, 0.5f);
  vertices[33].tex = glm::vec2(0.0f, 1.0f);
  vertices[34].pos = glm::vec3(-0.5f, -0.5f, -0.5f);
  vertices[34].tex = glm::vec2(1.0f, 1.0f);
  vertices[35].pos = glm::vec3(0.5f, -0.5f, -0.5f);
  vertices[35].tex = glm::vec2(1.0f, 0.0f);

  m_mesh->m_clientSideVertices = vertices;
  m_mesh->m_clientSideIndices = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35 };
  m_mesh->m_material = Main::GetInstance()->m_materialManager.Create(MaterialPath("default.material"));
}

ABT::Cube::~Cube()
{
}

ABT::EntityType ABT::Cube::GetType()
{
  return EntityType::Entity_Cube;
}

ABT::Quad::Quad()
{
  std::vector<ABT::Vertex> vertices;
  vertices.resize(4);

  // Front
  vertices[0].pos = glm::vec3(-0.5f, 0.5f, 0.0f);
  vertices[0].tex = glm::vec2(0.0f, 1.0f);
  vertices[0].norm = glm::vec3(0.0f, 0.0f, 1.0f);
  vertices[0].btan = glm::vec3(0.0f, 1.0f, 0.0f);

  vertices[1].pos = glm::vec3(-0.5f, -0.5f, 0.0f);
  vertices[1].tex = glm::vec2(0.0f, 0.0f);
  vertices[1].norm = glm::vec3(0.0f, 0.0f, 1.0f);
  vertices[1].btan = glm::vec3(0.0f, 1.0f, 0.0f);

  vertices[2].pos = glm::vec3(0.5f, -0.5f, 0.0f);
  vertices[2].tex = glm::vec2(1.0f, 0.0f);
  vertices[2].norm = glm::vec3(0.0f, 0.0f, 1.0f);
  vertices[2].btan = glm::vec3(0.0f, 1.0f, 0.0f);

  vertices[3].pos = glm::vec3(0.5f, 0.5f, 0.0f);
  vertices[3].tex = glm::vec2(1.0f, 1.0f);
  vertices[3].norm = glm::vec3(0.0f, 0.0f, 1.0f);
  vertices[3].btan = glm::vec3(0.0f, 1.0f, 0.0f);

  m_mesh->m_clientSideVertices = vertices;
  m_mesh->m_clientSideIndices = { 0,1,2,0,2,3 };
  m_mesh->m_material = Main::GetInstance()->m_materialManager.Create(MaterialPath("default.material"));
}

ABT::Quad::~Quad()
{
}

ABT::EntityType ABT::Quad::GetType()
{
  return EntityType::Entity_Quad;
}

ABT::Sphere::Sphere()
{
  const float r = 1.0f;
  const int nRings = 32;
  const int nSegments = 32;

  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  float fDeltaRingAngle = (glm::pi<float>() / nRings);
  float fDeltaSegAngle = (glm::two_pi<float>() / nSegments);
  unsigned short wVerticeIndex = 0;

  // Generate the group of rings for the sphere
  for (int ring = 0; ring <= nRings; ring++) 
  {
    float r0 = r * sinf(ring * fDeltaRingAngle);
    float y0 = r * cosf(ring * fDeltaRingAngle);

    // Generate the group of segments for the current ring
    for (int seg = 0; seg <= nSegments; seg++) 
    {
      float x0 = r0 * sinf(seg * fDeltaSegAngle);
      float z0 = r0 * cosf(seg * fDeltaSegAngle);

      // Add one vertex to the strip which makes up the sphere
      Vertex v;
      v.pos = glm::vec3(x0, y0, z0);
      v.norm = glm::vec3(x0, y0, z0);
      v.tex = glm::vec2((float)seg / (float)nSegments, (float)ring / (float)nRings);

      float r2, zenith, azimuth;
      ToSpherical(v.pos, r2, zenith, azimuth);
      v.btan = glm::vec3(r * glm::cos(zenith) * glm::sin(azimuth), -r * glm::sin(zenith), r * glm::cos(zenith) * glm::cos(azimuth));

      vertices.push_back(v);

      if (ring != nRings) 
      {
        // each vertex (except the last) has six indicies pointing to it
        indices.push_back(wVerticeIndex + nSegments + 1);
        indices.push_back(wVerticeIndex);
        indices.push_back(wVerticeIndex + nSegments);
        indices.push_back(wVerticeIndex + nSegments + 1);
        indices.push_back(wVerticeIndex + 1);
        indices.push_back(wVerticeIndex);
        wVerticeIndex++;
      }
    } // end for seg
  } // end for ring

  m_mesh->m_clientSideVertices = vertices;
  m_mesh->m_clientSideIndices = indices;
  m_mesh->m_material = Main::GetInstance()->m_materialManager.Create(MaterialPath("default.material"));
}

  ABT::Sphere::~Sphere()
{
}

ABT::EntityType ABT::Sphere::GetType()
{
  return EntityType::Entity_Sphere;
}
