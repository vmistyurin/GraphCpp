#ifndef UNIT_TESTS_COMPARATORS_H
#define UNIT_TESTS_COMPARATORS_H

#include "core/edge.h"
#include "gtest/gtest.h"
#include <vector>
#include <set>
#include <algorithm>

namespace graphcpp_testing
{
    using namespace graphcpp;
	template<class T>
	inline bool compare_vectors_without_order(const std::vector<T>& v1, const std::vector<T>& v2)
	{
		RETURN_IF(v1.size() != v2.size(), false);
		for (std::vector<T>::size_type i = 0; i < v1.size(); i++)
		{
			RETURN_IF(!CONTAINS(v1, v2[i]), false);
			RETURN_IF(!CONTAINS(v2, v1[i]), false);
		}
		return true;
	}
}
#endif
