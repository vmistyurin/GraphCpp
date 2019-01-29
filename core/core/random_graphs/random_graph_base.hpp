#pragma once

#include <vector>

#include "core/macroses.hpp"

namespace graphcpp 
{
	class RandomGraphBase 
	{
	public:
		virtual msize dimension() const = 0;
		virtual mcontent at(msize index1, msize index2) const = 0;
		virtual void set(msize index1, msize index2, mcontent value) = 0;

        virtual double probability_at(msize index1, msize index2) const = 0;
		virtual void set_probability(msize index1, msize index2, double value) = 0;

		virtual void delete_vertexes(const std::vector<msize>& vertexes) = 0;
		
		ABSTRACT_CLASS_OPERATIONS(RandomGraphBase)
	};
}
