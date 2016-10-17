// ThreadSafeQueue.tpp

// HTP Includes
#include <HTP/ThreadSafeQueue.hpp>

#ifdef __HTP_THREADSAFEQUEUE_HPP__

namespace HTP
{
  template<typename T> ThreadSafeQueue<T>::ThreadSafeQueue() : Queue<T>()
  {
  }

  template<typename T> ThreadSafeQueue<T>::~ThreadSafeQueue()
  {
  }

  template<typename T> bool ThreadSafeQueue<T>::IsEmpty()
  {
    m_Mutex.Lock();
    bool isEmpty = Queue<T>::IsEmpty();
    m_Mutex.Unlock();

    return isEmpty;
  }

  template<typename T> int ThreadSafeQueue<T>::GetSize()
  {
    m_Mutex.Lock();
    int size = Queue<T>::GetSize();
    m_Mutex.Unlock();

    return size;
  }

  template<typename T> void ThreadSafeQueue<T>::Push(T p_Data)
  {
    m_Mutex.Lock();
    Queue<T>::Push(p_Data);
    m_Condition.Signal();
    m_Mutex.Unlock();
  }

  template<typename T> T ThreadSafeQueue<T>::Pop()
  {
    m_Mutex.Lock();
    while(IsEmpty())
    {
      m_Condition.Wait(&m_Mutex);
    }
    T data = Queue<T>::Pop();
    m_Mutex.Unlock();

    return data;
  }
}

#endif
