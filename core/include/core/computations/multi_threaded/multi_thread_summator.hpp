#pragma once

#include <condition_variable>
#include <mutex>

#include "core/utils.hpp"

namespace graphcpp
{
    template<class SummableType>
    class MultiThreadSummator final
    {
    private:
        SummableType _sum;
        double _probability = 0;
        
        mutable std::mutex _add_mutex;
        
        mutable std::mutex _cv_mutex;
        std::condition_variable _cv;
        
    public:
        explicit MultiThreadSummator(SummableType&& initial);
        
        template<class SummableCompatibleType>
        void add(SummableCompatibleType&& addend, double probability);
        
        double current_probability() const;
        SummableType wait_for_result();
    };
    
    template<class SummableType>
    MultiThreadSummator<SummableType>::MultiThreadSummator(SummableType&& initial) :
        _sum(std::move(initial))
    {
    }
    
    template<class SummableType>
    template<class SummableCompatibleType>
    void MultiThreadSummator<SummableType>::add(SummableCompatibleType&& addend, double probability)
    {
        std::lock_guard lock(_add_mutex);

        addend *= probability;
        _sum += addend;
        _probability += probability;
        
        if (are_doubles_equal(_probability, 1))
        {
            std::unique_lock lock(_cv_mutex);
            _cv.notify_one();
        }
    }
    
    template<class SummableType>
    double MultiThreadSummator<SummableType>::current_probability() const
    {
        return _probability;
    }
    
    template<class SummableType>
    SummableType MultiThreadSummator<SummableType>::wait_for_result()
    {
        std::unique_lock lock(_cv_mutex);
        _cv.wait(lock);
        
        assert(are_doubles_equal(_probability, 1));
        
        return _sum;
    }
}
