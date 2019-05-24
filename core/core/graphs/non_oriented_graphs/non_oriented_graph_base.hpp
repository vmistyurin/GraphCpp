#pragma once

#include <list> 
#include <memory>

#include "core/graphs/graph_base.hpp"
#include "core/iterators/symmetric_matrix_iterator.hpp"
#include "core/edges/symmetric_edge.hpp"

namespace graphcpp
{
	class SymmetricMatrixBase;
} 

namespace graphcpp
{
	class NonOrientedGraphBase : public GraphBase
	{
	public:
		virtual std::vector<SymmetricEdge> get_edges() const = 0;
        virtual msize get_number_of_edges() const = 0;
        
		virtual std::unique_ptr<SymmetricMatrixBase> get_matrix() const = 0;
		
		virtual std::list<std::pair<msize, msize>> get_hanged_vertexes() const = 0;
		virtual std::vector<msize> get_connected_component(msize vertex) const = 0;
		virtual std::vector<std::vector<msize>> get_connected_components() const = 0;
        
        virtual std::list<std::vector<msize>> get_connected_trees() const = 0;

		std::pair<std::list<std::pair<msize, msize>>, std::vector<msize>> get_bridges() const;
		std::vector<std::vector<msize>> get_chains() const;

        bool is_tree() const;

		SymmetricMatrixIterator begin() const;
		SymmetricMatrixIterator end() const;

        ABSTRACT_CLASS_OPERATIONS(NonOrientedGraphBase)
	};
    
    std::vector<msize> get_hinges(const NonOrientedGraphBase& graph);
}
