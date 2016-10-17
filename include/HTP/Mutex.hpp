// Mutex.hpp

#ifndef __HTP_MUTEX_HPP__
#define __HTP_MUTEX_HPP__

// SDL2 Includes
#include <SDL2/SDL_thread.h>

namespace HTP
{
  class Condition;
  class Mutex
  {
    friend class Condition;

    public:
      Mutex();
      ~Mutex();

      void Lock();
      void Unlock();

    private:
      SDL_mutex* GetWrappedObject();

    private:
      SDL_mutex* m_Mutex;
  };
}

#endif
