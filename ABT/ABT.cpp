#include "stdafx.h"
#include "ABT.h"
#include "Logger.h"

std::string ABT::TexturePath(std::string file)
{
  std::string path = "../Resources/Textures/";
  path += file;
  return path;
}

std::string ABT::MeshPath(std::string file)
{
  std::string path = "../Resources/Meshes/";
  path += file;
  return path;
}

std::string ABT::FontPath(std::string file)
{
  std::string path = "../Resources/Fonts/";
  path += file;
  return path;
}

std::string ABT::SpritePath(std::string file)
{
  std::string path = "../Resources/Sprites/";
  path += file;
  return path;
}

std::string ABT::AudioPath(std::string file)
{
  std::string path = "../Resources/Audio/";
  path += file;
  return path;
}

std::string ABT::AnimationPath(std::string file)
{
  std::string path = "../Resources/Meshes/";
  path += file;
  return path;
}

std::string ABT::SkeletonPath(std::string file)
{
  std::string path = "../Resources/Meshes/";
  path += file;
  return path;
}

std::string ABT::ShaderPath(std::string file)
{
  std::string path = "../Resources/Shaders/";
  path += file;
  return path;
}

std::string ABT::MaterialPath(std::string file)
{
  std::string path = "../Resources/Materials/";
  path += file;
  return path;
}

ABT::Main ABT::Main::m_instance;

ABT::Main::~Main()
{
}

void ABT::Main::Init()
{
  Logger::GetInstance()->Log("ABT Initialization");
  m_animationMan.Init();
  m_textureMan.Init();
  m_meshMan.Init();
  m_skinMeshMan.Init();
  m_spriteSheetMan.Init();
  m_audioMan.Init();
  m_shaderMan.Init();
  m_materialManager.Init();
  
  m_initiated = true;
}

void ABT::Main::Uninit()
{
  m_animationPlayer.m_records.clear();
  m_animationMan.Uninit();
  m_textureMan.Uninit();
  m_meshMan.Uninit();
  m_skinMeshMan.Uninit();
  m_spriteSheetMan.Uninit();
  m_audioMan.Uninit();
  m_shaderMan.Uninit();
  m_materialManager.Uninit();

  m_initiated = false;
}

ABT::Main::Main()
{
}

ABT::Main* ABT::Main::GetInstance()
{
  return &m_instance;
}
