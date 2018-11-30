#pragma once

#include <list> 
#include <memory>

#include "core/graph_implementations/graph_base.hpp"
#include "core/iterators/symmetric_matrix_iterator.hpp"
#include "core/edges/symmetric_edge.hpp"
#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"

namespace graphcpp
{
	class NonOrientedGraphBase : public GraphBase
	{
	public:
		virtual std::vector<SymmetricEdge> get_edges() const = 0;
        virtual msize get_number_of_edges() const = 0;
        
		virtual std::unique_ptr<SymmetricMatrixBase> get_matrix() const = 0;
		virtual std::unique_ptr<NonOrientedGraphBase> extract_subgraph(const std::vector<msize>& vertexes) const = 0;

		virtual std::list<std::pair<msize, msize>> get_hanged_vertexes() const = 0;
		virtual std::vector<msize> get_connected_component(msize vertex) const = 0;
		virtual std::vector<std::vector<msize>> get_connected_components() const = 0;
        
        virtual std::list<std::vector<msize>> get_connected_trees() const = 0;

		std::pair<std::list<std::pair<msize, msize>>, std::vector<msize>> get_bridges() const;
		std::vector<std::vector<msize>> get_chains() const;

        bool is_tree() const;
        
		virtual std::unique_ptr<NonOrientedGraphBase> with_deleted_vertexes(const std::vector<msize>& vertexes) const = 0;
		virtual std::unique_ptr<NonOrientedGraphBase> with_deleted_edge(msize i, msize j) const = 0;

		SymmetricMatrixIterator begin() const;
		SymmetricMatrixIterator end() const;

        ABSTRACT_CLASS_OPERATIONS(NonOrientedGraphBase);
	};
}
