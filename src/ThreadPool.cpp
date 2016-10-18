// ThreadPool.cpp

// HTP Includes
#include <HTP/ThreadPool.hpp>

namespace HTP
{
  int ThreadPool::ThreadWorker(void* p_Data)
  {
    const unsigned long id = SDL_GetThreadID(nullptr);

    ThreadPool* pool = static_cast<ThreadPool*>(p_Data);
    pool->Process(id);

    return 0;
  }

  ThreadPool::ThreadPool(int p_ThreadCount)
  {
    int maximumThreadCount = SDL_GetCPUCount();

    m_IsStopped = false;
    m_ThreadCount = (maximumThreadCount < p_ThreadCount) ? maximumThreadCount : p_ThreadCount;

    for (int i = 0; i < m_ThreadCount; ++i)
    {
      SDL_Thread* thread = SDL_CreateThread(ThreadWorker, "HybridThreadPool", this);

      if (thread != nullptr)
      {
        m_Threads.push_back(thread);
      }
      else
      {
        SDL_Log("[HTP::ThreadPool] Failed to create thread: %s", SDL_GetError());

        --m_ThreadCount;
      }
    }

    SDL_Log("[HTP::ThreadPool] Created ThreadPool with %d threads.", m_ThreadCount);
  }

  ThreadPool::~ThreadPool()
  {
    m_IsStopped = true;
    m_Semaphore.Increment(m_ThreadCount);

    for (SDL_Thread* thread : m_Threads)
    {
      SDL_WaitThread(thread, nullptr);
    }

    SDL_Log("[HTP::ThreadPool] Destroyed ThreadPool.");
  }

  bool ThreadPool::IsStopped()
  {
    return m_IsStopped;
  }

  int ThreadPool::GetThreadCount()
  {
    return m_ThreadCount;
  }

  void ThreadPool::Process(unsigned long p_ThreadID)
  {
      SDL_Log("[Thread #%lu] Starting...", p_ThreadID);

      while (!IsStopped())
      {
        m_Semaphore.Wait();

        if (!IsStopped())
        {
          std::function<void()> task = m_Tasks.Pop();
          task();
        }
      }

      SDL_Log("[Thread #%lu] Finishing...", p_ThreadID);
  }
}
