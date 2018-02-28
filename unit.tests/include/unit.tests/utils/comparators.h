#ifndef GRAPHCPP_PROJECT_COMPARATORS_H
#define GRAPHCPP_PROJECT_COMPARATORS_H

#include "core/edge.h"
#include "gtest/gtest.h"
#include <vector>
#include <set>
#include <algorithm>

namespace graphcpp_testing
{
    using namespace graphcpp;
    inline bool AreVectorsOfEdgesEqual(const std::vector<Edge>& v1, const std::vector<Edge>& v2) //TODO: Remove
    {
		RETURN_IF(v1.size() != v2.size(), false);
        for(std::vector<Edge>::size_type i = 0; i < v1.size(); i++)
        {
			RETURN_IF(std::find(v1.cbegin(), v1.cend(), v2[i]) == v1.cend(), false);
			RETURN_IF(std::find(v2.cbegin(), v2.cend(), v1[i]) == v2.cend(), false);
        }
        return true;
    }

	template<class T>
	inline bool CompareVectorsWithoutOrder(const std::vector<T>& v1, const std::vector<T>& v2)
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
#endif //GRAPHCPP_PROJECT_COMPARATORS_H
