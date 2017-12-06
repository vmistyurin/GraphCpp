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
    inline bool IsVectorOfEdgesAreEqual(const std::vector<Edge>& v1, const std::vector<Edge>& v2)
    {
        if(v1.size() != v2.size())
        {
            return false;
        }
        for(std::vector<Edge>::size_type i = 0; i < v1.size(); i++)
        {
            if (std::find(v1.cbegin(), v1.cend(), v2[i]) == v1.cend())
            {
                return false;
            }
            if (std::find(v2.cbegin(), v2.cend(), v1[i]) == v2.cend())
            {
                return false;
            }
        }
        return true;
    }
}
#endif //GRAPHCPP_PROJECT_COMPARATORS_H
