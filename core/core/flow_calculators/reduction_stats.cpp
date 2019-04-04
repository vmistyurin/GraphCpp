#include "core/flow_calculators/reduction_stats.hpp"

#include <cassert>

using namespace graphcpp;
using namespace graphcpp::flow_calculators;

namespace
{
    std::string hanged_vertexes_stats(const ReductionStats& stats)
    {
        return "Hanged vertexes: " + std::to_string(stats.get_hanged_vertexes_counter());
    }

    std::string stdmap_to_string(const std::map<size_t, size_t>& map) 
    {
        auto result = std::string();

        for(const auto&[size, amount] : map)
        {
            result.append("\n\t");
            result.append(std::to_string(size) + " -> " + std::to_string(amount));
        }

        return result;
    }

    std::string calculated_trees_stats(const ReductionStats& stats)
    {
        auto result = std::string("Calculated trees sizes: ");
        result.append(stdmap_to_string(stats.get_calculated_trees_stats()));

        return result;
    }

    std::string small_graph_stats(const ReductionStats& stats)
    {
        auto result = std::string("Small graphs sizes: ");
        result.append(stdmap_to_string(stats.get_small_graphs_stats()));

        return result;
    }
}

ReductionStats::ReductionStats() :
    _hanged_vertexes(0)
{
}

void ReductionStats::increase_hanged_vertexes_counter(size_t amount)
{
    assert(amount != 0);

    _hanged_vertexes+= amount;
}

msize ReductionStats::get_hanged_vertexes_counter() const
{
    return _hanged_vertexes;
}

void ReductionStats::register_calculated_tree(size_t tree_size)
{
    std::lock_guard lock(_calculated_trees_mutex);

    _calculated_trees_sizes[tree_size]++;
}

std::map<size_t, size_t> ReductionStats::get_calculated_trees_stats() const
{
    std::lock_guard lock(_calculated_trees_mutex);

    return _calculated_trees_sizes;
}

void ReductionStats::register_small_graph(size_t dimension)
{
    std::lock_guard lock(_small_graphs_mutex);

    _small_graphs[dimension]++;
}

std::map<size_t, size_t> ReductionStats::get_small_graphs_stats() const
{
    std::lock_guard lock(_small_graphs_mutex);

    return _small_graphs;
}

std::ostream& graphcpp::flow_calculators::operator<< (std::ostream& stream, const ReductionStats& stats)
{
    stream << std::endl << "Reduction stats: " << std::endl;

    stream << hanged_vertexes_stats(stats) << std::endl;
    stream << calculated_trees_stats(stats) << std::endl;
    stream << small_graph_stats(stats) << std::endl;

    return stream;
}
