#pragma once

#include <mutex>

namespace graphcpp
{
    template<class SummableType>
    class Summator final
    {
    private:
        double _probability;
        SummableType _sum;
        
        mutable std::mutex _mutex;
        
    public:
        Summator(SummableType&& initial_sum);
        void add(SummableType&& addend, double probability);
        SummableType wait_for_result();
    };
    
    template<class SummableType>
    Summator<SummableType>::Summator(SummableType&& initial_sum) :
         _probability(0.0), _sum(std::move(initial_sum))
    {
    }
    
    template<class SummableType>
    void Summator<SummableType>::add(SummableType&& addend, double probability)
    {
        std::lock_guard _(_mutex);
        
        _probability += _probability;
        //_sum += addend;
        
        if (_probability == 1)
        {
            return;
        }
    }
    
    template<class SummableType>
    SummableType Summator<SummableType>::wait_for_result()
    {
        
    }
}
