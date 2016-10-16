// Queue.hpp

#ifndef __HTP_QUEUE__
#define __HTP_QUEUE__

namespace HTP
{
  template<typename T> class Queue
  {
    struct QueueNode
    {
      T Data;
      QueueNode* Next;
    };

    public:
      Queue();
      virtual ~Queue();

      virtual bool IsEmpty();
      virtual int GetSize();

      virtual void Push(T p_Data);
      virtual T Pop();

    private:
      int m_Size;
      QueueNode* m_Head;
      QueueNode* m_Tail;
  };
}

// Template Definition Include
#include <HTP/Queue.tpp>

#endif
