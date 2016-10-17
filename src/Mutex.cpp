// ThreadPool.cpp

// HTP Includes
#include <HTP/Mutex.hpp>
// SDL2 Includes
#include <SDL2/SDL.h>

namespace HTP
{
  Mutex::Mutex()
  {
    m_Mutex = SDL_CreateMutex();
    if (m_Mutex == nullptr)
    {
      SDL_Log("[HTP::Mutex] Failed to create mutex: %s", SDL_GetError());
    }
  }

  Mutex::~Mutex()
  {
    SDL_DestroyMutex(m_Mutex);
  }

  void Mutex::Lock()
  {
    if (SDL_LockMutex(m_Mutex) < 0)
    {
      SDL_Log("[HTP::Mutex] Error locking mutex: %s", SDL_GetError());
    }
  }

  void Mutex::Unlock()
  {
    if (SDL_UnlockMutex(m_Mutex) < 0)
    {
      SDL_Log("[HTP::Mutex] Error unlocking mutex: %s", SDL_GetError());
    }
  }

  SDL_mutex* Mutex::GetWrappedObject()
  {
    return m_Mutex;
  }
}
