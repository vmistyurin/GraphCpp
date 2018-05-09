#ifndef GRAPH_CORE_NON_ORIENTED_GRAPH_BASE_HPP
#define GRAPH_CORE_NON_ORIENTED_GRAPH_BASE_HPP

#include <list> 

#include "core/graph_implementations/graph_base.hpp"
#include "core/iterators/symmetric_matrix_iterator.hpp"
#include "core/symmetrical_edge.hpp"
#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"

namespace graphcpp
{
	class NonOrientedGraphBase : public GraphBase
	{
	public:
		virtual std::vector<SymmetricalEdge> get_edges() const = 0;
		virtual std::shared_ptr<SymmetricMatrixBase> get_matrix() const = 0;
		virtual std::shared_ptr<NonOrientedGraphBase> extract_subgraph(const std::vector<msize>& vertexes) const = 0;

		virtual std::list<std::pair<msize, msize>> get_hanged_vertexes() const = 0;
		virtual std::vector<msize> get_connected_component(msize vertex) const = 0;
		virtual std::vector<std::vector<msize>> get_connected_components() const = 0;

		std::list<std::pair<msize, msize>> get_bridges() const;

		SymmetricMatrixIterator begin() const;
		SymmetricMatrixIterator end() const;

		virtual ~NonOrientedGraphBase() = default;
		NonOrientedGraphBase() = default;
		NonOrientedGraphBase(const NonOrientedGraphBase&) = default;
		NonOrientedGraphBase& operator=(const NonOrientedGraphBase&) = default;
		NonOrientedGraphBase(NonOrientedGraphBase&&) = default;
		NonOrientedGraphBase& operator=(NonOrientedGraphBase&&) = default;
	};
}
#endif