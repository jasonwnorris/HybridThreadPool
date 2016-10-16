// ThreadPool.tpp

// HTP Includes
#include <HTP/ThreadPool.hpp>

#ifdef __HTP_THREADPOOL__

namespace HTP
{
  template<class F, class... Args> std::future<typename std::result_of<F(Args...)>::type> ThreadPool::Start(F&& p_Function, Args&&... p_Arguments)
  {
    if (m_IsStopped)
    {
      SDL_Log("[HTP::ThreadPool] Attempted to start new task on stopped ThreadPool.");
    }

    auto binding = std::bind(std::forward<F>(p_Function), std::forward<Args>(p_Arguments)...);
    auto task = std::make_shared<std::packaged_task<typename std::result_of<F(Args...)>::type()>>(binding);
    auto future = task->get_future();

    LockMutex();
    m_Tasks.Push([task]() { (*task)(); });
    SignalCondition();
    UnlockMutex();

    return future;
  }
}

#endif
