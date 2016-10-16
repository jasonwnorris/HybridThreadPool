// ThreadPool.cpp

// HTP Includes
#include <HTP/ThreadPool.hpp>

namespace HTP
{
  int ThreadPool::ThreadWorker(void* p_Data)
  {
    const unsigned long id = SDL_GetThreadID(nullptr);

    SDL_Log("[Thread #%lu] Starting...", id);

    ThreadPool* pool = static_cast<ThreadPool*>(p_Data);
    bool assigned = false;

    while (!pool->IsStopped())
    {
      std::function<void()> task;

      pool->LockMutex();

      if (!pool->IsStopped())
      {
        pool->WaitCondition();
      }

      if (!pool->IsStopped())
      {
        task = pool->NextTask();
        assigned = true;
      }

      pool->UnlockMutex();

      if (!pool->IsStopped() && assigned)
      {
        task();
        assigned = false;
      }
    }

    SDL_Log("[Thread #%lu] Finishing...", id);

    return 0;
  }

  ThreadPool::ThreadPool(int p_ThreadCount) : ThreadSafe()
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
    LockMutex();
    m_IsStopped = true;
    BroadcastCondition();
    UnlockMutex();

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

  std::function<void()> ThreadPool::NextTask()
  {
    return m_Tasks.Pop();
  }
}
