// Condition.hpp

#ifndef __HTP_CONDITION_HPP__
#define __HTP_CONDITION_HPP__

// SDL2 Includes
#include <SDL2/SDL_thread.h>

namespace HTP
{
  class Mutex;
  class Condition
  {
    public:
      Condition();
      ~Condition();

      void Broadcast();
      void Signal();
      void Wait(Mutex* p_Mutex);

    private:
      SDL_cond* m_Condition;
  };
}

#endif
