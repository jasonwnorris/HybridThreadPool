// main.cpp

// HTP Includes
#include <HTP/ThreadPool.hpp>
// STL Includes
#include <iostream>

int CubeInteger(int p_Value)
{
  return p_Value * p_Value * p_Value;
}

void TestThreadSafeQueue()
{
  HTP::ThreadSafeQueue<int> queue;

  for (int i = 0; i < 10; ++i)
  {
    queue.Push(i * i);
  }

  while (!queue.IsEmpty())
  {
    std::cout << queue.Pop() << std::endl;
  }
}

void TestThreadPool()
{
  HTP::ThreadPool pool(8);

  std::vector<std::future<int>> results;
  for (int i = 0; i < 16; ++i)
  {
    results.push_back(pool.Start(CubeInteger, i));
  }

  for (std::future<int>& result : results)
  {
    std::cout << result.get() << std::endl;
  }
}

int main(int p_ArgCount, char** p_ArgVars)
{
  TestThreadSafeQueue();
  TestThreadPool();

  return 0;
}
