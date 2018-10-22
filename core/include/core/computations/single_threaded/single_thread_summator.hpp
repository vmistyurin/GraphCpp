#pragma once

#include "core/utils.hpp"

namespace graphcpp
{
	template<class SummableType>
	class SingleThreadSummator final
	{
	private:
		SummableType _sum;
		double _probability;

	public:
		explicit SingleThreadSummator(SummableType&& initial);

		void add(SummableType&& addend, double probability);

		double current_probability() const;
		SummableType current_sum() const;
	};

	template<class SummableType>
	SingleThreadSummator<SummableType>::SingleThreadSummator(SummableType&& initial) :
		_sum(std::move(initial)), _probability(0)
	{
	}

	template<class SummableType>
	void SingleThreadSummator<SummableType>::add(SummableType&& addend, double probability)
	{
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