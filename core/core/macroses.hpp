#pragma once

#include <cstddef>
#include <limits>
#include <type_traits>

#define RETURN_IF(condition, value) if(condition) return value;
#define MINMAX(value1, value2) if(value1 > value2) std::swap(value1, value2)

#define ABSTRACT_CLASS_OPERATIONS(ClassName) \
    virtual ~ClassName() = default; \
    ClassName() = default; \
    ClassName(const ClassName&) = default; \
    ClassName& operator=(const ClassName&) = default; \
    ClassName(ClassName&&) = default; \
    ClassName& operator=(ClassName&&) = default;

#define UNREACHABLE() std::abort()

namespace graphcpp
{
	using msize = size_t;
	using mcontent = double; //TODO: Template it

	constexpr static auto msize_undefined = std::numeric_limits<msize>::max();
	constexpr static auto mcontent_undefined = std::numeric_limits<mcontent>::max();
}

namespace graphcpp
{
	class SymmetricMatrixBase;
	class NonOrientedGraphBase;
	class RandomNonOrientedGraphBase;

	#define IS_SYM_MATRIX_IMPL(MatrixType) static_assert(std::is_base_of_v<SymmetricMatrixBase, MatrixType> && !std::is_abstract_v<MatrixType>)
	#define IS_NOR_GRAPH_IMPL(GraphType) static_assert(std::is_base_of_v<NonOrientedGraphBase, GraphType> && !std::is_abstract_v<GraphType>)
	#define IS_NOR_RANDOM_GRAPH_IMPL(RandomGraphType) static_assert(std::is_base_of_v<RandomNonOrientedGraphBase, RandomGraphType> && !std::is_abstract_v<RandomGraphType>)
}
