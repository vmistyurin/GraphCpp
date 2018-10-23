#pragma once

#include "core/utils.hpp"

namespace graphcpp
{
	template<class SummableType>
	class SingleThreadSummator final
	{
	private:
		SummableType _sum;
		double _probability = 0;

	public:
		explicit SingleThreadSummator(SummableType&& initial);

        template<class SummableCompatibleType>
		void add(SummableCompatibleType&& addend, double probability);

		double current_probability() const;
		SummableType current_sum() const;
	};

	template<class SummableType>
	SingleThreadSummator<SummableType>::SingleThreadSummator(SummableType&& initial) :
		_sum(std::move(initial))
	{
	}

    template<class SummableType>
    template<class SummableCompatibleType>
	void SingleThreadSummator<SummableType>::add(SummableCompatibleType&& addend, double probability)
	{
        addend *= probability;
		_sum += addend;
		_probability += probability;
	}

	template<class SummableType>
	double SingleThreadSummator<SummableType>::current_probability() const
	{
		return _probability;
	}

	template<class SummableType>
	SummableType SingleThreadSummator<SummableType>::current_sum() const
	{
		return _sum;
	}
}
