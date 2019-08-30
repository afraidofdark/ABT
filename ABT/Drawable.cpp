#include "stdafx.h"
#include "Drawable.h"
#include "Mesh.h"
#include "Material.h"
#include "ABT.h"

ABT::Drawable::Drawable()
{
  m_mesh = std::shared_ptr<Mesh> (new Mesh());
}

ABT::Drawable::~Drawable()
{
}

ABT::EntityType ABT::Drawable::GetType()
{
  return EntityType::Entity_Drawable;
}

bool ABT::Drawable::IsDrawable()
{
  return true;
}

void ABT::Drawable::SetPose(Animation* anim)
{
  if (m_mesh->IsSkinned())
  {
    Skeleton* skeleton = ((SkinMesh*)m_mesh.get())->m_skeleton;
    anim->GetCurrentPose(skeleton);
  }
  else
  {
    anim->GetCurrentPose(m_node);
  }
}
