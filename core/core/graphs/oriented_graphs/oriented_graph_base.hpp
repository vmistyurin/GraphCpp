#pragma once

#include <memory>

#include "core/edges/edge.hpp"
#include "core/iterators/matrix_iterator.hpp"
#include "core/graphs/graph_base.hpp"

namespace graphcpp
{
	class MatrixBase;
}

namespace graphcpp
{
	class OrientedGraphBase : public GraphBase
	{
	public:
		virtual std::vector<Edge> get_edges() const = 0;
		virtual std::unique_ptr<MatrixBase> get_matrix() const = 0;
		virtual std::unique_ptr<OrientedGraphBase> extract_subgraph(const std::vector<msize>& vertexes) const = 0;

		MatrixIterator begin() const;
		MatrixIterator end() const;

		ABSTRACT_CLASS_OPERATIONS(OrientedGraphBase)
	};
}
