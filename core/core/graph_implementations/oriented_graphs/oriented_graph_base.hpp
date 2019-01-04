#pragma once

#include <memory>

#include "core/edges/edge.hpp"
#include "core/iterators/matrix_iterator.hpp"
#include "core/graph_implementations/graph_base.hpp"
#include "core/matrix_implementations/matrix_base.hpp"
#include "core/matrix_implementations/matrix_implementations.hpp"

namespace graphcpp
{
	class OrientedGraphBase : public GraphBase
	{
	public:
		virtual std::vector<Edge> get_edges() const = 0;
		virtual std::unique_ptr<SingleVectorMatrix> get_matrix() const = 0;
		virtual std::unique_ptr<OrientedGraphBase> extract_subgraph(const std::vector<msize>& vertexes) const = 0;

		MatrixIterator begin() const;
		MatrixIterator end() const;

		ABSTRACT_CLASS_OPERATIONS(OrientedGraphBase)
	};
}
