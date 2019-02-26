#pragma once

#include <thread>
#include <vector>
#include <queue>
#include <future>

namespace graphcpp
{
    class ThreadPool final
    {
    private:
        std::atomic<bool> _done;
        std::mutex _mutex;
        std::condition_variable _cv;
        
        std::queue<std::function<void()>> _tasks;
        std::vector<std::thread> _threads;
        
        void thread_work();
        
    public:
        ThreadPool(unsigned number_of_threads = std::thread::hardware_concurrency());
        ~ThreadPool();
        
        template<class FunctionType>
        void add_task(FunctionType&& task);
    };
    
    template<class FunctionType>
    void ThreadPool::add_task(FunctionType&& f)
    {        
        std::lock_guard lock(_mutex);

        _tasks.push(std::forward<FunctionType>(f));
        _cv.notify_one();
    }
}