// ThreadPool.cpp

// HTP Includes
#include <HTP/ThreadSafe.hpp>
// SDL2 Includes
#include <SDL2/SDL.h>

namespace HTP
{
  ThreadSafe::ThreadSafe()
  {
    m_Mutex = SDL_CreateMutex();
    if (m_Mutex == nullptr)
    {
      SDL_Log("[HTP::ThreadSafe] Failed to create mutex: %s", SDL_GetError());
    }

    m_Condition = SDL_CreateCond();
    if (m_Condition == nullptr)
    {
      SDL_Log("[HTP::ThreadSafe] Failed to create condition: %s", SDL_GetError());
    }
  }

  ThreadSafe::~ThreadSafe()
  {
    SDL_DestroyMutex(m_Mutex);
    SDL_DestroyCond(m_Condition);
  }

  void ThreadSafe::LockMutex()
  {
    if (SDL_LockMutex(m_Mutex) < 0)
    {
      SDL_Log("[HTP::ThreadSafe] Error locking mutex: %s", SDL_GetError());
    }
  }

  void ThreadSafe::UnlockMutex()
  {
    if (SDL_UnlockMutex(m_Mutex) < 0)
    {
      SDL_Log("[HTP::ThreadSafe] Error unlocking mutex: %s", SDL_GetError());
    }
  }

  void ThreadSafe::BroadcastCondition()
  {
    if (SDL_CondBroadcast(m_Condition) < 0)
    {
      SDL_Log("[HTP::ThreadSafe] Error broadcasting condition: %s", SDL_GetError());
    }
  }

  void ThreadSafe::SignalCondition()
  {
    if (SDL_CondSignal(m_Condition) < 0)
    {
      SDL_Log("[HTP::ThreadSafe] Error signalling condition: %s", SDL_GetError());
    }
  }

  void ThreadSafe::WaitCondition()
  {
    if (SDL_CondWait(m_Condition, m_Mutex) < 0)
    {
      SDL_Log("[HTP::ThreadSafe] Error waiting on condition: %s", SDL_GetError());
    }
  }
}
