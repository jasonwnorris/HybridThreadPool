// ThreadSafeQueue.tpp

// HTP Includes
#include <HTP/ThreadSafeQueue.hpp>

#ifdef __HTP_THREADSAFEQUEUE__

namespace HTP
{
  template<typename T> ThreadSafeQueue<T>::ThreadSafeQueue() : Queue<T>(), ThreadSafe()
  {
  }

  template<typename T> ThreadSafeQueue<T>::~ThreadSafeQueue()
  {
  }

  template<typename T> bool ThreadSafeQueue<T>::IsEmpty()
  {
    LockMutex();
    bool isEmpty = Queue<T>::IsEmpty();
    UnlockMutex();

    return isEmpty;
  }

  template<typename T> int ThreadSafeQueue<T>::GetSize()
  {
    LockMutex();
    int size = Queue<T>::GetSize();
    UnlockMutex();

    return size;
  }

  template<typename T> void ThreadSafeQueue<T>::Push(T p_Data)
  {
    LockMutex();
    Queue<T>::Push(p_Data);
    SignalCondition();
    UnlockMutex();
  }

  template<typename T> T ThreadSafeQueue<T>::Pop()
  {
    LockMutex();
    while(IsEmpty())
    {
      WaitCondition();
    }
    T data = Queue<T>::Pop();
    UnlockMutex();

    return data;
  }
}

#endif
