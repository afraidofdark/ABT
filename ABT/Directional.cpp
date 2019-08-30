#include "stdafx.h"
#include "Directional.h"
#include "Node.h"

ABT::Directional::Directional()
{
}

ABT::Directional::~Directional()
{
}

void ABT::Directional::Pitch(float val)
{
  glm::quat q = glm::angleAxis(val, glm::vec3(1.0f, 0.0f, 0.0f));
  m_node->Rotate(q, ABT::TS_LOCAL);
}

void ABT::Directional::Yaw(float val)
{
  glm::quat q = glm::angleAxis(val, glm::vec3(0.0f, 1.0f, 0.0f));
  m_node->Rotate(q, ABT::TS_LOCAL);
}

void ABT::Directional::Roll(float val)
{
  glm::quat q = glm::angleAxis(val, glm::vec3(1.0f, 0.0f, 0.0f));
  m_node->Rotate(q, ABT::TS_LOCAL);
}

void ABT::Directional::Translate(glm::vec3 pos)
{
  m_node->Translate(pos, ABT::TS_LOCAL);
}

void ABT::Directional::RotateOnUpVector(float val)
{
  m_node->Rotate(glm::angleAxis(val, glm::vec3(0.0f, 1.0f, 0.0f)), ABT::TS_WORLD);
}

void ABT::Directional::GetLocalAxis(glm::vec3& dir, glm::vec3& up, glm::vec3& right)
{
  glm::mat4 transform = m_node->GetTransform();
  right = glm::column(transform, 0);
  up = glm::column(transform, 1);
  dir = -glm::column(transform, 2);
}

ABT::EntityType ABT::Directional::GetType()
{
  return EntityType::Entity_Directional;
}

ABT::Camera::Camera()
{
  SetLens(glm::radians(90.0f), 640.0f, 480.0f, 0.01f, 1000.0f);
}

ABT::Camera::~Camera()
{
}

void ABT::Camera::SetLens(float fov, float width, float height, float near, float far)
{
  m_projection = glm::perspectiveFov(fov, width, height, near, far);
}

void ABT::Camera::SetLens(float aspect, float left, float right, float bottom, float top, float near, float far)
{
  m_projection = glm::ortho(left * aspect, right * aspect, bottom, top, near, far);
}

glm::mat4 ABT::Camera::GetViewMatrix()
{
  glm::mat4 view = m_node->GetTransform(ABT::TS_WORLD);
  return glm::inverse(view);
}

ABT::Camera::CamData ABT::Camera::GetData()
{
  CamData data;
  glm::vec3 tmp;
  GetLocalAxis(data.dir, data.pos, tmp);
  data.pos = m_node->GetTranslation(ABT::TS_WORLD);

  return data;
}

ABT::EntityType ABT::Camera::GetType()
{
  return EntityType::Entity_Camera;
}

ABT::Light::Light()
{
  m_color = glm::vec3(1.0f, 1.0f, 1.0f);
}

ABT::Light::~Light()
{
}

ABT::Light::LightData ABT::Light::GetData()
{
  LightData data;
  GetLocalAxis(data.dir, data.pos, data.color);
  data.pos = m_node->GetTranslation(ABT::TS_WORLD);
  data.color = m_color;

  return data;
}

ABT::EntityType ABT::Light::GetType()
{
  return EntityType::Entity_Light;
}
