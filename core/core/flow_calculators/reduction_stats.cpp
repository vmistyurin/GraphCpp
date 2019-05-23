#include "core/flow_calculators/reduction_stats.hpp"

#include <cassert>
#include <string>

using namespace graphcpp;
using namespace graphcpp::flow_calculators;

namespace
{
    std::string hanged_vertexes_stats(const ReductionStats& stats)
    {
        return "Hanged vertexes: " + std::to_string(stats.get_hanged_vertexes_counter());
    }

	std::string bridges_stats(const ReductionStats& stats)
	{
		return "Bridges: " + std::to_string(stats.get_bridges_counter());
	}

	std::string hinges_stats(const ReductionStats& stats)
	{
		return "Hinges: " + std::to_string(stats.get_hinges_counter());
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

	std::string small_random_graph_stats(const ReductionStats& stats)
	{
		auto result = std::string("Small random graphs sizes: ");
		result.append(stdmap_to_string(stats.get_small_random_graphs_stats()));

		return result;
	}

	std::string disconnected_components_stats(const ReductionStats& stats)
	{
		auto result = std::string("Disconnected component sizes: ");
		result.append(stdmap_to_string(stats.get_disconnected_components_stats()));

		return result;
	}

	std::string chains_stats(const ReductionStats& stats)
	{
		auto result = std::string("Chains stats: ");
		result.append(stdmap_to_string(stats.get_chains_stats()));

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

    _hanged_vertexes += amount;
}

size_t ReductionStats::get_hanged_vertexes_counter() const
{
    return _hanged_vertexes;
}

void ReductionStats::register_bridges(size_t amount)
{
	assert(amount != 0);

	_bridges += amount;
}

size_t ReductionStats::get_bridges_counter() const
{
	return _bridges;
}

void ReductionStats::register_hinge(size_t amount)
{
	assert(amount != 0);

	_hinges += amount;
}

size_t ReductionStats::get_hinges_counter() const
{
	return _hinges;
}

void ReductionStats::register_calculated_tree(size_t tree_size)
{
	_calculated_trees_sizes.perform_function([=](std::map<size_t, size_t>& map)
	{
		map[tree_size]++;
	});
}

const std::map<size_t, size_t>& ReductionStats::get_calculated_trees_stats() const
{
	return _calculated_trees_sizes.value();
}

void ReductionStats::register_small_graph(size_t dimension)
{
	_small_graphs.perform_function([=](std::map<size_t, size_t>& map)
	{
		map[dimension]++;
	});
}

const std::map<size_t, size_t>& ReductionStats::get_small_graphs_stats() const
{
	return _small_graphs.value();
}

void ReductionStats::register_small_random_graph(size_t dimension)
{
	_small_random_graphs.perform_function([=](std::map<size_t, size_t>& map)
	{
		map[dimension]++;
	});
}

const std::map<size_t, size_t>& ReductionStats::get_small_random_graphs_stats() const
{
	return _small_random_graphs.value();
}

void ReductionStats::register_disconnected_component(size_t dimension)
{
    _disconnected_components.perform_function([=](std::map<size_t, size_t>& map)
    {
        map[dimension]++;
    });
}

const std::map<size_t, size_t>& ReductionStats::get_disconnected_components_stats() const
{
    return _disconnected_components.value();
}

void ReductionStats::register_chain(size_t size)
{
	_chains.perform_function([=](std::map<size_t, size_t>& map)
	{
		map[size]++;
	});
}

const std::map<size_t, size_t>& ReductionStats::get_chains_stats() const
{
	return _chains.value();
}

std::ostream& graphcpp::flow_calculators::operator<< (std::ostream& stream, const ReductionStats& stats)
{
    stream << std::endl << "Reduction stats: " << std::endl;

    stream << hanged_vertexes_stats(stats) << std::endl;
	stream << bridges_stats(stats) << std::endl;
	stream << hinges_stats(stats) << std::endl;

    //stream << calculated_trees_stats(stats) << std::endl;
	stream << disconnected_components_stats(stats) << std::endl;
	stream << chains_stats(stats) << std::endl;
    stream << small_graph_stats(stats) << std::endl;
	stream << small_random_graph_stats(stats) << std::endl;

    return stream;
}
