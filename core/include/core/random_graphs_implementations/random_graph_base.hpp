#pragma once


#include <vector>
#include <string>

#include "core/macroses.hpp"


namespace graphcpp 
{
	class RandomGraphBase 
	{
	public:
		virtual msize dimension() const = 0;
		virtual mcontent at(msize index1, msize index2) const = 0;
		virtual void set(msize index1, msize index2, mcontent value) = 0;
		virtual void reduce_element(msize index1, msize index2, mcontent difference) = 0;

		virtual const std::vector<double>& probabilities() const = 0;

		virtual void rearrange_with_permutations(const std::vector<msize>& new_nums) = 0;
		virtual void rearrange_with_allocate(const std::vector<msize>& new_nums) = 0;
		void make_rearranged(const std::vector<msize>& new_nums, RandomGraphBase& memory) const;
				
		virtual ~RandomGraphBase() = default;
		RandomGraphBase() = default;
		RandomGraphBase(const RandomGraphBase&) = default;
		RandomGraphBase& operator=(const RandomGraphBase&) = default;
		RandomGraphBase(RandomGraphBase&&) = default;
		RandomGraphBase& operator=(RandomGraphBase&&) = default;
	};
}
