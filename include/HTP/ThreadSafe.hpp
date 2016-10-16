// ThreadSafeQueue.hpp

#ifndef __HTP_THREADSAFE__
#define __HTP_THREADSAFE__

// SDL2 Includes
#include <SDL2/SDL_thread.h>

namespace HTP
{
  class ThreadSafe
  {
    public:
      ThreadSafe();
      ~ThreadSafe();

    protected:
      void LockMutex();
      void UnlockMutex();
      void BroadcastCondition();
      void SignalCondition();
      void WaitCondition();

    private:
      SDL_mutex* m_Mutex;
      SDL_cond* m_Condition;
  };
}

#endif
