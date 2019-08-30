#pragma once

#include "Cube.h"
#include "Node.h"
#include "Material.h"

class Player : public ABT::Cube
{
public:
  Player()
  {
    m_parent.AddChild(m_node);
    m_node->Translate(glm::vec3(0.5f, 0.5f, 0.5f));
    Translate(glm::vec3(0.5f, 0.5f, 0.5f));
    m_mesh->m_material->m_diffuseTexture = ABT::Main::m_textureMan.Create("..\\Resources\\Textures\\question.png");
  }

  void Translate(glm::vec3 val)
  {
    m_parent.Translate(val);
  }

  void RotateVerticalPlus()
  {
    static int rot = 0;

    if (rot == 0)
    {
      if (m_prevTask != RotationTask::Vertical_Plus)
      {
        glm::vec3 ts = m_node->GetTranslation(ABT::TS_WORLD);
        m_parent.m_translation = ts + glm::vec3(-0.5f, -0.5f, -0.5f);
        m_node->Translate(glm::vec3(1.0, 0, 1.0), ABT::TS_WORLD);
      }
    }

    if (rot < 90)
    {
      rot += m_animSpeed;
      m_parent.Rotate(glm::angleAxis(glm::radians((float)m_animSpeed), ABT::Z_AXIS));
    }
    else
    {
      rot = 0;
      m_parent.Translate(glm::vec3(-1.0f, 0.0f, 0.0f), ABT::TS_WORLD);
      m_node->Translate(glm::vec3(1.0f, 0.0f, 0.0f), ABT::TS_WORLD);
      m_taskList.erase(m_taskList.end() - 1);
    }
  }

  void RotateVerticalMinus()
  {
    static int rot = 0;

    if (rot == 0)
    {
      if (m_prevTask != RotationTask::Vertical_Minus && m_prevTask != RotationTask::Horizontal_Plus)
      {
        glm::vec3 ts = m_node->GetTranslation(ABT::TS_WORLD);
        m_parent.m_translation = ts + glm::vec3(0.5f, -0.5f, 0.5f);
        m_node->Translate(glm::vec3(-1.0, 0, -1.0), ABT::TS_WORLD);
      }
    }

    if (rot < 90)
    {
      rot += m_animSpeed;
      m_parent.Rotate(glm::angleAxis(glm::radians(-(float)m_animSpeed), ABT::Z_AXIS));
    }
    else
    {
      rot = 0;
      m_parent.Translate(glm::vec3(1.0f, 0.0f, 0.0f), ABT::TS_WORLD);
      m_node->Translate(glm::vec3(-1.0f, 0.0f, 0.0f), ABT::TS_WORLD);
      m_taskList.erase(m_taskList.end() - 1);
    }
  }

  void RotateHorizontalPlus()
  {
    static int rot = 0;

    if (rot == 0)
    {
      if (m_prevTask != RotationTask::Horizontal_Plus && m_prevTask != RotationTask::Vertical_Minus)
      {
        glm::vec3 ts = m_node->GetTranslation(ABT::TS_WORLD);
        m_parent.m_translation = ts + glm::vec3(0.5f, -0.5f, 0.5f);
        m_node->Translate(glm::vec3(-1.0, 0, -1.0), ABT::TS_WORLD);
      }
    }

    if (rot < 90)
    {
      rot += m_animSpeed;
      m_parent.Rotate(glm::angleAxis(glm::radians((float)m_animSpeed), ABT::X_AXIS));
    }
    else
    {
      rot = 0;
      m_parent.Translate(glm::vec3(0.0f, 0.0f, 1.0f), ABT::TS_WORLD);
      m_node->Translate(glm::vec3(0.0f, 0.0f, -1.0f), ABT::TS_WORLD);
      m_taskList.erase(m_taskList.end() - 1);
    }
  }

  void RotateHorizontalMinus()
  {
    static int rot = 0;

    if (rot == 0)
    {
      if (m_prevTask != RotationTask::Horizontal_Minus && m_prevTask != RotationTask::Vertical_Plus)
      {
        glm::vec3 ts = m_node->GetTranslation(ABT::TS_WORLD);
        m_parent.m_translation = ts + glm::vec3(0.5f, -0.5f, 0.5f);
        m_node->Translate(glm::vec3(1.0, 0, 1.0), ABT::TS_WORLD);
      }
    }

    if (rot < 90)
    {
      rot += m_animSpeed;
      m_parent.Rotate(glm::angleAxis(glm::radians(-(float)m_animSpeed), ABT::X_AXIS));
    }
    else
    {
      rot = 0;
      m_parent.Translate(glm::vec3(0.0f, 0.0f, -1.0f), ABT::TS_WORLD);
      m_node->Translate(glm::vec3(0.0f, 0.0f, 1.0f), ABT::TS_WORLD);
      m_taskList.erase(m_taskList.end() - 1);
    }
  }

  enum RotationTask
  {
    Vertical_Plus,
    Vertical_Minus,
    Horizontal_Plus,
    Horizontal_Minus
  };

  int m_animSpeed = 1;
  ABT::Node m_parent;
  RotationTask m_prevTask = Vertical_Plus;
  std::vector<RotationTask> m_taskList;
};