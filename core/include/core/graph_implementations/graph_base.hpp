#ifndef GRAPH_CORE_GRAPH_BASE_HPP
#define GRAPH_CORE_GRAPH_BASE_HPP

#include <vector>
#include <memory>
#include <list>

#include "core/matrix_implementations/matrix_base.hpp"

namespace graphcpp
{
	class GraphBase
	{
	public:
		virtual msize dimension() const = 0;
		virtual mcontent at(msize v1, msize v2) const = 0;
		virtual void set(msize v1, msize v2, mcontent value) = 0;

		virtual bool equal(const GraphBase& other) const = 0;

		virtual std::vector<msize> get_linked_vertexes(msize vertex) const = 0;
        virtual std::vector<msize> get_degrees() const = 0;
		virtual msize get_degree(msize vertex) const = 0;

		virtual void delete_vertexes(const std::vector<msize>& vertexes) = 0;
		virtual void rearrange(const std::vector<msize>& new_nums) = 0;

		virtual ~GraphBase() = default;
		GraphBase() = default;
		GraphBase(const GraphBase&) = default;
		GraphBase& operator=(const GraphBase&) = default;
		GraphBase(GraphBase&&) = default;
		GraphBase& operator=(GraphBase&&) = default;
	};
}
#endif