#pragma once

#include <algorithm>

#include "core/macroses.hpp"

namespace graphcpp_testing
{
    template<class ContainerType>
    bool compare_without_order(const ContainerType& first,
                               const ContainerType& second)
    {
        RETURN_IF(std::size(first) != std::size(second), false);
        for (typename ContainerType::size_type i = 0; i < std::size(first); i++)
        {
            RETURN_IF(std::find(std::cbegin(first), std::cend(first), *std::next(std::cbegin(second), i)) == std::cend(first), false);
            RETURN_IF(std::find(std::cbegin(second), std::cend(second), *std::next(std::cbegin(first), i)) == std::cend(second), false);
        }
        return true;
    }
}
