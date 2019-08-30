#pragma once

namespace ABT
{

  class Node;
  class Animation;

  enum EntityType
  {
    Entity_Base,
    Entity_AudioSource,
    Entity_Actor,
    Entity_Cube,
    Entity_Quad,
    Entity_Sphere,
    Entity_Drawable,
    Entity_SpriteAnim,
    Entity_Surface,
    Entity_Directional,
    Entity_Light,
    Entity_Camera
  };

  class Entity
  {
  public:
    Entity();
    virtual ~Entity();

    virtual bool IsDrawable();
    virtual EntityType GetType();
    virtual void SetPose(Animation* anim);

  public:
    Node* m_node = nullptr;
  };

}