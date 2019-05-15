#pragma once

#include <vector>
#include <optional>

#include "core/macroses.hpp"

namespace graphcpp
{
	class GraphBase
	{
	public:
		virtual msize dimension() const = 0;
		virtual mcontent at(msize v1, msize v2) const = 0;
		virtual void set(msize v1, msize v2, mcontent value) = 0;
		virtual void add_vertex() = 0;
		void reduce_edge(msize v1, msize v2, mcontent amount);

		virtual bool equal(const GraphBase& other) const = 0;

		std::vector<msize> get_linked_vertexes(msize vertex) const;
        std::vector<msize> get_degrees() const;
		msize get_degree(msize vertex) const;

		virtual std::vector<msize> delete_vertexes(const std::vector<msize>& vertexes) = 0;
		virtual void rearrange(const std::vector<msize>& new_nums) = 0;

		ABSTRACT_CLASS_OPERATIONS(GraphBase)
	};

	std::optional<std::vector<msize>> get_random_path(const GraphBase& graph, msize start, msize finish);
	std::vector<msize> get_connected_component(const GraphBase& graph, msize vertex);
}