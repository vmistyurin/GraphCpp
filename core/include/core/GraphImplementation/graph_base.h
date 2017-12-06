#ifndef GRAPH_CORE_GRAPHBASE_H
#define GRAPH_CORE_GRAPHBASE_H
#include "core/edge.h"
#include "core/macroses.h"
#include <vector>

namespace graphcpp
{
	struct GraphBase
	{
		virtual ~GraphBase() = default;

		virtual const SymmetricMatrixBase& get_matrix() const = 0;
        virtual std::vector<msize> get_degrees() const = 0;
		virtual msize get_degree(msize vertex) const = 0;
		virtual std::vector<Edge> get_edges() const = 0;
		virtual msize dimension() const = 0;
		virtual std::vector<msize> get_linked_vertexes(msize vertex) const = 0;
		virtual void delete_vertexes(const std::vector<msize>& vertexes) = 0;
		virtual bool equal(const GraphBase& other) const = 0;
		virtual void rearrange(const std::vector<msize>& new_nums) = 0;
	};
}
#endif