#include "core/utils/thread_pool.hpp"

#include <functional>

#include "core/utils/defer.hpp"

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

void ThreadPool::thread_work()
{
	_working_threads++;

    while (true)
    {
        std::unique_lock lock(_mutex);
        
        _cv.wait(lock, [&]
        {
            if (_done)
            {				
                return true;
            }

			if (_waiting_for_stop && _tasks.empty())
			{
				return true;
			}

            return !_tasks.empty();
        });

		if (_waiting_for_stop && _tasks.empty())
		{
			if (_working_threads.fetch_sub(1) == 1)
			{
				_stop_promise.set_value();
			}
			break;
		}
        
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

std::future<void> ThreadPool::wait_for_stop()
{
	_waiting_for_stop = true;
	return _stop_promise.get_future();
}
