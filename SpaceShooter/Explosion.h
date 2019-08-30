#pragma once

#include "ABT.h"
#include "Node.h"
#include "Directional.h"


class ExplosionManager
{
public:
  ~ExplosionManager()
  {
    for (auto entry : m_sprites)
      SafeDel(entry);
  }

  void SpawnMeteorExplosion(glm::vec2 pos)
  {
    std::shared_ptr<ABT::SpriteSheet> spriteSheet = ABT::Main::GetInstance()->m_spriteSheetMan.Create(ABT::SpritePath("explosion.sprites"));
    ABT::SpriteAnimation* anim = new ABT::SpriteAnimation(spriteSheet);
    anim->m_node->m_translation = glm::vec3(pos.x, pos.y, 0.0f);
    anim->m_animFps = 30.0f;
    for (int i = 0; i < (int)spriteSheet->m_sprites.size(); i++)
      anim->m_frames.push_back(std::to_string(i));
    m_sprites.push_back(anim);
  }

  void SpawnShipExplosion(glm::vec2 pos)
  {
    std::shared_ptr<ABT::SpriteSheet> spriteSheet = ABT::Main::GetInstance()->m_spriteSheetMan.Create(ABT::SpritePath("shipExplosion.sprites"));
    ABT::SpriteAnimation* anim = new ABT::SpriteAnimation(spriteSheet);
    anim->m_node->m_translation = glm::vec3(pos.x, pos.y, 0.0f);
    anim->m_animFps = 30.0f;
    for (int i = 0; i < (int)spriteSheet->m_sprites.size(); i++)
      anim->m_frames.push_back(std::to_string(i));

    m_sprites.push_back(anim);
  }

  void Update(float deltaTime)
  {
    for (int i = (int)m_sprites.size() - 1; i > -1; i--)
    {
      if (m_sprites[i]->m_animationStoped)
      {
        SafeDel(m_sprites[i]);
        m_sprites.erase(m_sprites.begin() + i);
      }
      else
      {
        m_sprites[i]->Update(deltaTime);
      }
    }
  }

  std::vector<ABT::SpriteAnimation*> m_sprites;
};