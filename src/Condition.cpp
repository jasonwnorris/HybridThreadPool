// Condition.cpp

// HTP Includes
#include <HTP/Condition.hpp>
#include <HTP/Mutex.hpp>
// SDL2 Includes
#include <SDL2/SDL.h>

namespace HTP
{
  Condition::Condition()
  {
    m_Condition = SDL_CreateCond();
    if (m_Condition == nullptr)
    {
      SDL_Log("[HTP::Condition] Failed to create condition: %s", SDL_GetError());
    }
  }

  Condition::~Condition()
  {
    SDL_DestroyCond(m_Condition);
  }

  void Condition::Broadcast()
  {
    if (SDL_CondBroadcast(m_Condition) < 0)
    {
      SDL_Log("[HTP::Condition] Error broadcasting condition: %s", SDL_GetError());
    }
  }

  void Condition::Signal()
  {
    if (SDL_CondSignal(m_Condition) < 0)
    {
      SDL_Log("[HTP::Condition] Error signalling condition: %s", SDL_GetError());
    }
  }

  void Condition::Wait(Mutex* p_Mutex)
  {
    if (SDL_CondWait(m_Condition, p_Mutex->GetWrappedObject()) < 0)
    {
      SDL_Log("[HTP::Condition] Error waiting on condition: %s", SDL_GetError());
    }
  }
}
