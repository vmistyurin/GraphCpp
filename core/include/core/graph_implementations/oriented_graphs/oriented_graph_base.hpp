#ifndef GRAPH_CORE_ORIENTED_GRAPH_BASE_HPP
#define GRAPH_CORE_ORIENTED_GRAPH_BASE_HPP

#include <memory>

#include "core/edges/edge.hpp"
#include "core/iterators/matrix_iterator.hpp"
#include "core/graph_implementations/graph_base.hpp"
#include "core/matrix_implementations/matrix_base.hpp"

namespace graphcpp
{
	class OrientedGraphBase : public GraphBase
	{
	public:
		virtual std::vector<Edge> get_edges() const = 0;
		virtual std::shared_ptr<MatrixBase> get_matrix() const = 0;
		virtual std::shared_ptr<OrientedGraphBase> extract_subgraph(const std::vector<msize>& vertexes) const = 0;

		MatrixIterator begin() const;
		MatrixIterator end() const;

		virtual ~OrientedGraphBase() = default;
		OrientedGraphBase() = default;
		OrientedGraphBase(const OrientedGraphBase&) = default;
		OrientedGraphBase& operator=(const OrientedGraphBase&) = default;
		OrientedGraphBase(OrientedGraphBase&&) = default;
		OrientedGraphBase& operator=(OrientedGraphBase&&) = default;
	};
}
#endif