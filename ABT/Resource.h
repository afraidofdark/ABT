#pragma once

#include <assert.h>
#include <string>

namespace ABT
{

  class Resource
  {
  public:
    virtual ~Resource() {}
    virtual void Load() = 0;
    virtual void Init(bool flushClientSideArray = true) = 0;
    virtual Resource* GetCopy() { assert(false); return nullptr; }

  public:
    std::string m_file;
    bool m_loaded = false;
    bool m_initiated = false;
  };

}