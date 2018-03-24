#ifndef GRAPH_CORE_GRAPH_BASE_H
#define GRAPH_CORE_GRAPH_BASE_H

#include "core/edge.h"
#include "core/macroses.h"
#include "core/MatrixImplementation/symmetric_matrix_base.h"
#include <vector>
#include <memory>
#include <list>

namespace graphcpp
{
	class GraphBase
	{
	public:
		virtual ~GraphBase() = default;

		virtual msize dimension() const = 0;
		virtual bool equal(const GraphBase& other) const = 0;
		virtual const SymmetricMatrixBase& get_matrix() const = 0;
		virtual std::vector<Edge> get_edges() const = 0;

		virtual std::vector<msize> get_linked_vertexes(msize vertex) const = 0;
		virtual std::list<std::pair<msize, msize>> get_hanged_vertexes() const = 0;
		virtual std::vector<msize> get_connected_component(msize vertex) const = 0;
		virtual std::vector<std::vector<msize>> get_connected_components() const = 0;
		virtual std::shared_ptr<GraphBase> extract_subgraph(const std::vector<msize>& vertexes) const = 0;
        virtual std::vector<msize> get_degrees() const = 0;
		virtual msize get_degree(msize vertex) const = 0;

		virtual mcontent get_flow(msize source, msize sink) const = 0;
		virtual std::shared_ptr<SymmetricMatrixBase> get_matrix_of_flows() const = 0;
		virtual std::shared_ptr<SymmetricMatrixBase> optimized_get_matrix_of_flows() const = 0;

		virtual void delete_vertexes(const std::vector<msize>& vertexes) = 0;
		virtual void rearrange(const std::vector<msize>& new_nums) = 0;
	};
}
#endif