#pragma once

#include "DebugNew.h"
#include "ABT.h"
#include "Drawable.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"
#include "Ship.h"
#include "glm\gtc\random.hpp"

class PowerUp : public ABT::Drawable
{
public:

  PowerUp(std::shared_ptr<ABT::Mesh> pillObj)
  {
    m_mesh = pillObj;
    m_node->m_translation = glm::vec3(glm::linearRand(-10.0f, 10.0f), 0.0f, glm::linearRand(0.0f, -10.0f));
  }

  virtual void SetActor(Ship* actor) = 0;

  float m_time = 0;
  float m_duration = 0;
  const float m_collisionRad = 1.0f;

protected:
  Ship* m_actor = nullptr;

};

class FireRate2X : public PowerUp
{
public:

  FireRate2X(std::shared_ptr<ABT::Mesh> pillObj)
    : PowerUp(pillObj)
  {
    m_mesh->m_material = ABT::Main::GetInstance()->m_materialManager.Create(ABT::MaterialPath("pillBlue.material"));
    m_mesh->m_material->Init();
    m_duration = 30;
  }

  void SetActor(Ship* actor)
  {
    m_actor = actor;
    m_actor->m_fireRate = 8;
  }

  ~FireRate2X()
  {
    if (m_actor)
      m_actor->m_fireRate = 3;
  }

};

class ForPower : public PowerUp
{
public:

  ForPower(std::shared_ptr<ABT::Mesh> pillObj)
    : PowerUp(pillObj)
  {
    m_mesh->m_material = ABT::Main::GetInstance()->m_materialManager.Create(ABT::MaterialPath("pillRed.material"));
    m_mesh->m_material->Init();
    m_duration = 30;
  }

  void SetActor(Ship* actor)
  {
    m_actor = actor;
    m_actor->m_fireLocs.push_back(&actor->m_leftWing);
    m_actor->m_fireLocs.push_back(&actor->m_rightWing);
  }

  ~ForPower()
  {
    if (m_actor)
    {
      if (m_actor->m_fireLocs.size() == 4)
      {
        m_actor->m_fireLocs.pop_back();
        m_actor->m_fireLocs.pop_back();
      }
    }
  }

};

class PowerUpManager
{
public:

  PowerUpManager()
  {
    m_pillObj = ABT::Main::GetInstance()->m_meshMan.Create(ABT::MeshPath("pill.mesh"));
  }

  ~PowerUpManager()
  {
    for (auto entry : m_onGoingPowerUps)
      SafeDel(entry);

    for (auto entry : m_collectedPowerUps)
      SafeDel(entry);
  }

  template <class T>
  void Spawn()
  {
    // Client side copy sample
    std::shared_ptr<ABT::Mesh> meshCopy = std::shared_ptr<ABT::Mesh>(new ABT::Mesh());
    meshCopy->m_clientSideIndices = m_pillObj->m_clientSideIndices;
    meshCopy->m_clientSideVertices = m_pillObj->m_clientSideVertices;
    meshCopy->m_file = m_pillObj->m_file;
    meshCopy->Init();

    PowerUp* pop = new T(meshCopy);

    bool deleteMark = false;
    for (auto entry : m_onGoingPowerUps)
    {
      if (SphereSphereIntersection(
        entry->m_node->m_translation, entry->m_collisionRad,
        pop->m_node->m_translation, pop->m_collisionRad
      ))
      {
        deleteMark = true;
        break;
      }
    }

    if (deleteMark)
    {
      SafeDel(pop)
    }
    else
    {
      m_onGoingPowerUps.push_back(pop);
    }
  }

  void UpdateOnGoings(Ship* ship)
  {
    for (int i = (int)m_onGoingPowerUps.size() - 1; i > -1; i--)
    {
      PowerUp* pup = m_onGoingPowerUps[i];
      if (ship->CheckShipSphereCollision(pup->m_node->m_translation, pup->m_collisionRad))
      {
        pup->SetActor(ship);
        m_collectedPowerUps.push_back(pup);
        m_onGoingPowerUps.erase(m_onGoingPowerUps.begin() + i);
      }
      else
      {
        pup->m_node->Translate(ABT::Z_AXIS * 0.1f);
        pup->m_node->Rotate(glm::angleAxis(glm::radians(1.5f), ABT::X_AXIS));

        if (pup->m_node->m_translation.z >= 150.0f)
        {
          SafeDel(pup);
          m_onGoingPowerUps.erase(m_onGoingPowerUps.begin() + i);
        }
      }
    }
  }

  void UpdateCollecteds(float deltaTime)
  {
    for (int i = (int)m_collectedPowerUps.size() - 1; i > -1; i--)
    {
      PowerUp* pup = m_collectedPowerUps[i];
      pup->m_time += deltaTime;
      if (pup->m_time >= pup->m_duration)
      {
        SafeDel(pup);
        m_collectedPowerUps.erase(m_collectedPowerUps.begin() + i);
      }
    }
  }

  std::vector<PowerUp*> m_onGoingPowerUps;
  std::vector<PowerUp*> m_collectedPowerUps;
  std::shared_ptr<ABT::Mesh> m_pillObj;
};