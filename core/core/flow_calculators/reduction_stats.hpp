#pragma once

#include <atomic>
#include <map>
#include <mutex>
#include <ostream>

#include "core/macroses.hpp"

namespace graphcpp::flow_calculators
{
    class ReductionStats final
    {
    private:
        std::atomic<size_t> _hanged_vertexes;
        
        std::map<size_t, size_t> _calculated_trees_sizes; // size -> count
        mutable std::mutex _calculated_trees_mutex;

        std::map<size_t, size_t> _small_graphs; // size -> count
        mutable std::mutex _small_graphs_mutex;
    
    public:
        ReductionStats();

        void increase_hanged_vertexes_counter(size_t amount);
        msize get_hanged_vertexes_counter() const;

        void register_calculated_tree(size_t tree_size);
        std::map<size_t, size_t> get_calculated_trees_stats() const;

        void register_small_graph(size_t dimension);
        std::map<size_t, size_t> get_small_graphs_stats() const;
    };

    std::ostream& operator<< (std::ostream& stream, const ReductionStats& stats);
}