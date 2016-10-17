// ThreadSafeQueue.hpp

#ifndef __HTP_THREADSAFEQUEUE_HPP__
#define __HTP_THREADSAFEQUEUE_HPP__

// HTP Includes
#include <HTP/Condition.hpp>
#include <HTP/Mutex.hpp>
#include <HTP/Queue.hpp>

namespace HTP
{
  template<typename T> class ThreadSafeQueue : public Queue<T>
  {
    public:
      ThreadSafeQueue();
      ~ThreadSafeQueue();

      bool IsEmpty() override;
      int GetSize() override;

      void Push(T p_Data) override;
      T Pop() override;

    private:
      Mutex m_Mutex;
      Condition m_Condition;
  };
}

// Template Definition Include
#include <HTP/ThreadSafeQueue.tpp>

#endif
