// Semaphore.hpp

#ifndef __HTP_SEMAPHORE_HPP__
#define __HTP_SEMAPHORE_HPP__

// SDL2 Includes
#include <SDL2/SDL_thread.h>

namespace HTP
{
  class Semaphore
  {
    public:
      Semaphore(int p_InitialValue = 0);
      ~Semaphore();

      void Increment();
      void Increment(int p_Amount);
      void Wait();

    private:
      SDL_sem* m_Semaphore;
  };
}

#endif
