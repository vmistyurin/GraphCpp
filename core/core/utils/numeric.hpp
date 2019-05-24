#pragma once

#include <cassert>
#include <vector>
#include <algorithm>

#include "core/macroses.hpp"

namespace graphcpp
{
	class SymmetricMatrixBase;
	class NonSymmetricMatrixBase;
	class GraphBase;
}

namespace graphcpp
{
	bool is_permutation(const std::vector<msize>& candidate);
	std::vector<std::pair<msize, msize>> to_transpositions(const std::vector<msize>& permutation);

	bool check_symmetrical_matrix(const std::vector<std::vector<mcontent>>& candidate);
	bool is_matrix_from_graph(const SymmetricMatrixBase& matrix, const GraphBase& graph);
	bool is_matrix_from_graph(const NonSymmetricMatrixBase& matrix, const GraphBase& graph);
    bool are_doubles_equal(double value1, double value2);
    std::vector<msize> find_addition(const std::vector<msize>& numbers, msize length);
    std::vector<msize> reduce_vertexes_numbers(const std::vector<msize>& current_vertexes, const std::vector<msize>& missing_vertexes);
    
    template<class ValueType>
    void apply_permutation_with_transpositions(std::vector<ValueType>& target, const std::vector<msize>& permutation)
    {
        assert(is_permutation(permutation));
        assert(target.size() == permutation.size());
        
        auto transpositions = to_transpositions(permutation);
        
        for (auto[index1, index2] : transpositions)
        {
            std::swap(target[index1], target[index2]);
        }
    }
    
    template<class ContainerType, class ValueType>
    bool contains(const ContainerType& container, ValueType&& value)
    {
        return std::find(container.cbegin(), container.cend(), value) != container.cend();
    }
    
    template<class ValueType>
    std::vector<mcontent> apply_permutation_alloc(const std::vector<ValueType>& target, const std::vector<msize>& permutation)
    {
        assert(is_permutation(permutation));
        assert(target.size() == permutation.size());
        
        std::vector<mcontent> result(target.size());
        
        for (msize i = 0; i < target.size(); i++)
        {
            result[permutation[i]] = target[i];
        }
        
        return result;
    }
    
    template<class CollectionType, class ValueType>
    typename CollectionType::const_iterator binary_search(const CollectionType& collection, ValueType value)
    {
        assert(std::is_sorted(collection.cbegin(), collection.cend()));
        
        const auto it = std::lower_bound(collection.cbegin(), collection.cend(), value);
        if (it != collection.cend() && value != *it)
        {
            return collection.cend();
        }
        else
        {
            return it;
        }
    }
}
