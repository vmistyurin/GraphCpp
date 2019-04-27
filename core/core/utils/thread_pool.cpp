#include "core/utils/thread_pool.hpp"

#include <functional>

using namespace graphcpp;

ThreadPool::ThreadPool(unsigned number_of_threads) :
    _done(false)
{
    _threads.reserve(number_of_threads);
    
    for (unsigned i = 0; i < number_of_threads; i++)
    {
        _threads.emplace_back(&ThreadPool::thread_work, this);
    }
}

ThreadPool::~ThreadPool()
{
    _done = true;
    _cv.notify_all();
    
    std::for_each(_threads.begin(), _threads.end(), std::mem_fn(&std::thread::join));
}

ThreadPool& ThreadPool::shared()
{
    static auto threadPool = ThreadPool();
    return threadPool;
}

void ThreadPool::thread_work()
{
    while (true)
    {
        std::unique_lock lock(_mutex);
        
        _cv.wait(lock, [&]
        {
            if (_done)
            {
                return true;
            }
            return !_tasks.empty();
        });
        
        if (_done)
        {
            break;
        }
        
        auto task = _tasks.front();
        _tasks.pop();
        
        lock.unlock();
        
        task();
    }
}
