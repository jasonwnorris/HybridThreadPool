// ThreadPool.hpp

#ifndef __HTP_THREADPOOL_HPP__
#define __HTP_THREADPOOL_HPP__

// HTP Includes
#include <HTP/ThreadSafeQueue.hpp>
// SDL2 Includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
// STL Includes
#include <future>
#include <functional>
#include <vector>

namespace HTP
{
  class ThreadPool
  {
    public:
      static int ThreadWorker(void* p_Data);

    public:
      ThreadPool(int p_ThreadCount = 8);
      ~ThreadPool();

      bool IsStopped();
      int GetThreadCount();

      template<class F, class... Args> std::future<typename std::result_of<F(Args...)>::type> Start(F&& p_Function, Args&&... p_Arguments);

    private:
      void Process(unsigned long p_ThreadID);

    private:
      Mutex m_Mutex;
      Condition m_Condition;
      bool m_IsStopped;
      int m_ThreadCount;
      std::vector<SDL_Thread*> m_Threads;
      ThreadSafeQueue<std::function<void()>> m_Tasks;
  };
}

// Template Definition Include
#include <HTP/ThreadPool.tpp>

#endif
