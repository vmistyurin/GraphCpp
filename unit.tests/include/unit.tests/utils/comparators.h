#ifndef UNIT_TESTS_COMPARATORS_H
#define UNIT_TESTS_COMPARATORS_H

#include "gtest/gtest.h"
#include "core/macroses.h"
#include <vector>
#include <list>

namespace graphcpp_testing
{
	template<class T>
	inline bool compare_vectors_without_order(const std::vector<T>& v1, const std::vector<T>& v2)
	{
		RETURN_IF(v1.size() != v2.size(), false);
		for (typename std::vector<T>::size_type i = 0; i < v1.size(); i++)
		{
			RETURN_IF(!CONTAINS(v1, v2[i]), false);
			RETURN_IF(!CONTAINS(v2, v1[i]), false);
		}
		return true;
	}

	template<class T>
	inline bool compare_lists_without_order(const std::list<T>& l1, const std::list<T>& l2)
	{
		RETURN_IF(l1.size() != l2.size(), false);
		for (typename std::list<T>::size_type i = 0; i < l1.size(); i++)
		{
			RETURN_IF(!CONTAINS(l1, *std::next(l2.cbegin(), i)), false);
			RETURN_IF(!CONTAINS(l2, *std::next(l1.cbegin(), i)), false);
		}
		return true;
	}
}
#endif
