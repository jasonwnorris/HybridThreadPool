// Semaphore.cpp

// HTP Includes
#include <HTP/Semaphore.hpp>
// SDL2 Includes
#include <SDL2/SDL.h>

namespace HTP
{
  Semaphore::Semaphore(int p_InitialValue)
  {
    m_Semaphore = SDL_CreateSemaphore(p_InitialValue);
    if (m_Semaphore == nullptr)
    {
      SDL_Log("[HTP::Semaphore] Failed to create semaphore: %s", SDL_GetError());
    }
  }

  Semaphore::~Semaphore()
  {
    SDL_DestroySemaphore(m_Semaphore);
  }

  void Semaphore::Increment()
  {
    if (SDL_SemPost(m_Semaphore) < 0)
    {
      SDL_Log("[HTP::Semaphore] Error incrementing semaphore: %s", SDL_GetError());
    }
  }

  void Semaphore::Increment(int p_Amount)
  {
    if (p_Amount > 0)
    {
      for (int i = 0; i < p_Amount; ++i)
      {
        Increment();
      }
    }
  }

  void Semaphore::Wait()
  {
    if (SDL_SemWait(m_Semaphore) < 0)
    {
      SDL_Log("[HTP::Semaphore] Error waiting on semaphore: %s", SDL_GetError());
    }
  }
}
