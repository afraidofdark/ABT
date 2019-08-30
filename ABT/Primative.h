#pragma once

#include "Drawable.h"

namespace ABT
{

  class Cube : public Drawable
  {
  public:
    Cube();
    ~Cube();
    EntityType GetType();
  };

  class Quad : public Drawable
  {
  public:
    Quad();
    ~Quad();
    EntityType GetType();
  };

  class Sphere : public Drawable
  {
  public:
    Sphere();
    ~Sphere();
    EntityType GetType();
  };

}