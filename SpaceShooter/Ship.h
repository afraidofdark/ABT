#pragma once

#include "ABT.h"
#include "Mesh.h"
#include "Drawable.h"
#include "Directional.h"
#include "Node.h"
#include "MathUtil.h"
#include "glm\gtc\matrix_transform.hpp"
#include "DebugNew.h"

class Ship : public ABT::Drawable
{
public:
  Ship()
  {
    m_mesh->m_file = ABT::MeshPath("alien-mothership.mesh");
    m_mesh->Load();
    m_mesh->Init(false);

    // Create fire locations
    m_leftFireLoc.m_translation = glm::vec3(-1.0143f, 0.0173f, -0.7783f);
    m_node->AddChild(&m_leftFireLoc);
    m_leftWing.m_translation = glm::vec3(-2.7617f, -0.8409f, 0.5458);
    m_node->AddChild(&m_leftWing);

    m_rightFireLoc.m_translation = glm::vec3(1.0143f, 0.0173f, -0.7783f);
    m_node->AddChild(&m_rightFireLoc);
    m_rightWing.m_translation = glm::vec3(2.7617f, -0.8409f, 0.5458);
    m_node->AddChild(&m_rightWing);

    m_fireLocs.push_back(&m_leftFireLoc);
    m_fireLocs.push_back(&m_rightFireLoc);
  }

  bool CheckShipSphereCollision(glm::vec3 pos, float radius)
  {
    glm::mat4 transform = m_node->GetTransform();
    for (int i = 0; i < (int)m_mesh->m_clientSideVertices.size(); i++)
    {
      glm::vec3 vertex = m_mesh->m_clientSideVertices[i].pos;
      vertex = (transform * glm::vec4(vertex, 1.0f));
      if (SpherePointIntersection(pos, radius, vertex))
        return true;
    }

    return false;
  }

public:
  int m_fireRate = 3;
  std::vector<ABT::Node*> m_fireLocs;
  ABT::Node m_leftFireLoc;
  ABT::Node m_leftWing;
  ABT::Node m_rightFireLoc;
  ABT::Node m_rightWing;
};
