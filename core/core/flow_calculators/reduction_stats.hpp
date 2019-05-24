#pragma once

#include <atomic>
#include <map>
#include <ostream>

#include "core/macroses.hpp"
#include "core/utils/synchronized_value.hpp"

namespace graphcpp::flow_calculators
{
    class ReductionStats final
    {
    private:
        std::atomic<size_t> _hanged_vertexes = 0;
		std::atomic<size_t> _bridges = 0;
		std::atomic<size_t> _hinges = 0;
        
		SynchronizedValue<std::map<size_t, size_t>> _calculated_trees_sizes = SynchronizedValue(std::map<size_t, size_t>()); // size -> count

		SynchronizedValue<std::map<size_t, size_t>> _small_graphs = SynchronizedValue(std::map<size_t, size_t>()); // size -> count
		SynchronizedValue<std::map<size_t, size_t>> _small_random_graphs = SynchronizedValue(std::map<size_t, size_t>()); // size -> count

    
        SynchronizedValue<std::map<size_t, size_t>> _disconnected_components = SynchronizedValue(std::map<size_t, size_t>());
		SynchronizedValue<std::map<size_t, size_t>> _chains = SynchronizedValue(std::map<size_t, size_t>());
    
    public:
        ReductionStats();

        void increase_hanged_vertexes_counter(size_t amount);
		size_t get_hanged_vertexes_counter() const;

		void register_bridges(size_t amount);
		size_t get_bridges_counter() const;

		void register_hinge(size_t amount);
		size_t get_hinges_counter() const;

        void register_calculated_tree(size_t tree_size);
        const std::map<size_t, size_t>& get_calculated_trees_stats() const;

        void register_small_graph(size_t dimension);
        const std::map<size_t, size_t>& get_small_graphs_stats() const;

		void register_small_random_graph(size_t dimension);
		const std::map<size_t, size_t>& get_small_random_graphs_stats() const;
        
        void register_disconnected_component(size_t dimension);
        const std::map<size_t, size_t>& get_disconnected_components_stats() const;

		void register_chain(size_t dimension);
		const std::map<size_t, size_t>& get_chains_stats() const;
	};

    std::ostream& operator<< (std::ostream& stream, const ReductionStats& stats);
}
