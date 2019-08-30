#pragma once

#include "Surface.h"
#include "MathUtil.h"
#include "Resource.h"
#include "ResourceManager.h"

namespace ABT
{

  class Texture;
  class Vertex;

  struct SpriteEntry
  {
    std::string name;
    glm::vec2 offset;
    Rect<int> rectangle;
  };

  class SpriteSheet : public Resource
  {
  public:
    SpriteSheet();
    SpriteSheet(std::string file);
    ~SpriteSheet();

    void Load();
    void Init(bool flushClientSideArray = true);

  private:
    bool FetchEntries();
    std::vector<Vertex> CreateQuat(SpriteEntry val);

  public:
    std::shared_ptr<Texture> m_spriteSheet;
    std::vector<SpriteEntry> m_entries;
    std::string m_imageFile;
    int m_imageWidth;
    int m_imageHeight;

  public:
    std::unordered_map<std::string, ABT::Surface*> m_sprites;
  };

  class SpriteAnimation : public Drawable
  {
  public:
    SpriteAnimation();
    SpriteAnimation(std::shared_ptr<SpriteSheet> spriteSheet);
    ~SpriteAnimation();

    EntityType GetType();
    Surface* GetCurrentSurface();
    void Update(float deltaTime);

  public:
    float m_animFps = 23.4f;
    bool m_looping = false;
    bool m_animationStoped = false;
    std::vector<std::string> m_frames;
    std::shared_ptr<SpriteSheet> m_sheet;
    std::string m_currentFrame;

  private:
    float m_currentTime = 0.0f; // Seconds
    float m_prevTime = 0.0f;
  };

  class SpriteSheetManager : public ResourceManager<SpriteSheet>
  {
  };

}