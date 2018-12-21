#pragma once

#include <cstddef>
#include <limits>

#define RETURN_IF(condition, value) if(condition) return value;
#define MINMAX(value1, value2) if(value1 > value2) std::swap(value1, value2)

#define ABSTRACT_CLASS_OPERATIONS(ClassName) \
    virtual ~ClassName() = default; \
    ClassName() = default; \
    ClassName(const ClassName&) = default; \
    ClassName& operator=(const ClassName&) = default; \
    ClassName(ClassName&&) = default; \
    ClassName& operator=(ClassName&&) = default;

#define CRTP_CLASS_OPERATIONS(ClassName) \
    ClassName() = default; \
    ClassName(const ClassName&) = default; \
    ClassName& operator=(const ClassName&) = default; \
    ClassName(ClassName&&) = default; \
    ClassName& operator=(ClassName&&) = default;

namespace graphcpp
{
	using msize = size_t;
	using mcontent = double; //TODO: Template it

	constexpr static auto msize_undefined = std::numeric_limits<msize>::max();
	constexpr static auto mcontent_undefined = std::numeric_limits<mcontent>::max();
}
