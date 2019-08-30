#include "stdafx.h"
#include "Entity.h"
#include "Entity.h"
#include "Node.h"
#include "ABT.h"
#include "Skeleton.h"

ABT::Entity::Entity()
{
  m_node = new Node();
}

ABT::Entity::~Entity()
{
  SafeDel(m_node);
}

bool ABT::Entity::IsDrawable()
{
  return false;
}

ABT::EntityType ABT::Entity::GetType()
{
  return EntityType::Entity_Base;
}

void ABT::Entity::SetPose(Animation* anim)
{
  anim->GetCurrentPose(m_node);
}
