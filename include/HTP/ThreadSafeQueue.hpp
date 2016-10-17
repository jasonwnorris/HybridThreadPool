// ThreadSafeQueue.hpp

#ifndef __HTP_THREADSAFEQUEUE_HPP__
#define __HTP_THREADSAFEQUEUE_HPP__

// HTP Includes
#include <HTP/Queue.hpp>
#include <HTP/ThreadSafe.hpp>

namespace HTP
{
  template<typename T> class ThreadSafeQueue : public Queue<T>, public ThreadSafe
  {
    public:
      ThreadSafeQueue();
      ~ThreadSafeQueue();

      bool IsEmpty() override;
      int GetSize() override;

      void Push(T p_Data) override;
      T Pop() override;
  };
}

// Template Definition Include
#include <HTP/ThreadSafeQueue.tpp>

#endif
