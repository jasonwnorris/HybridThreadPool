// Queue.tpp

// HTP Includes
#include <HTP/Queue.hpp>

#ifdef __HTP_QUEUE_HPP__

namespace HTP
{
  template<typename T> Queue<T>::Queue()
  {
    m_Size = 0;
    m_Head = nullptr;
    m_Tail = nullptr;
  }

  template<typename T> Queue<T>::~Queue()
  {
    while (m_Head != nullptr)
    {
      Pop();
    }
  }

  template<typename T> bool Queue<T>::IsEmpty()
  {
    return m_Size == 0;
  }

  template<typename T> int Queue<T>::GetSize()
  {
    return m_Size;
  }

  template<typename T> void Queue<T>::Push(T p_Data)
  {
    QueueNode* node = new QueueNode();
    node->Data = p_Data;
    node->Next = nullptr;

    if (m_Head == nullptr)
    {
      m_Head = node;
      m_Tail = node;
    }
    else
    {
      m_Tail->Next = node;
      m_Tail = node;
    }

    ++m_Size;
  }

  template<typename T> T Queue<T>::Pop()
  {
    if (m_Head != nullptr)
    {
      T data = m_Head->Data;
      QueueNode* node = m_Head;

      m_Head = node->Next;

      delete node;

      --m_Size;

      return data;
    }
    else
    {
      // error
      return 0;
    }
  }
}

#endif
