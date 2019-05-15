#pragma once

#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/reduction_stats.hpp"

#include "core/flow_calculators/reductions/calculate_if_tree.hpp"
#include "core/flow_calculators/reductions/remove_connected_trees_reduction.hpp"
#include "core/flow_calculators/reductions/remove_hanged_vertexes_reduction.hpp"
#include "core/flow_calculators/reductions/split_to_components_reduction.hpp"

#include "core/flow_calculators/factorization.hpp"
#include "core/flow_calculators/random_graph_reductions/split_to_components.hpp"

namespace graphcpp::flow_calculators
{
    #define MAKE_REDUCTOR(function_name, next_reductor) std::bind(function_name<SymMatrixType, NorGraphType>, std::placeholders::_1, std::placeholders::_2, next_reductor) 

    template<class NorGraphType, class SymMatrixType>
    SymMatrixType reduction_use_algorithm(const NorGraphType& graph, single_flow_function_t<NorGraphType> flow_calc, ReductionStats* stats)
    {		
        using namespace graphcpp::flow_calculators::reductors;
        using reductor_type = std::function<SymMatrixType(NorGraphType, ReductionStats*)>;
         
        const reductor_type matrix_of_flows = std::bind(flow_calculators::matrix_of_flows<SymMatrixType, NorGraphType>, std::placeholders::_1, flow_calc);
        const reductor_type reduce_hanged_vertexes = MAKE_REDUCTOR(remove_hanged_vertexes, matrix_of_flows);
        const reductor_type reduce_connected_trees = MAKE_REDUCTOR(remove_connected_trees, reduce_hanged_vertexes); 
        const reductor_type check_trees = MAKE_REDUCTOR(calculate_if_tree, reduce_connected_trees); 

        return split_to_components(graph, stats, check_trees);
    }

    #undef MAKE_REDUCTOR

    #define MAKE_REDUCTOR(function_name, next_reductor) std::bind(function_name<RandomGraphType>, std::placeholders::_1, std::placeholders::_2, next_reductor) 
	class RandomGraphBase;

    template<class RandomGraphType>
	typename RandomGraphType::MatrixType reduction_use_algorithm_r(RandomGraphType random_graph, single_flow_function_t<typename RandomGraphType::GraphType> flow_calc, ReductionStats* stats, bool parallel)
    {
		using SymMatrixType = typename RandomGraphType::MatrixType;

		const reductor_t<RandomGraphType> factorization = [=](RandomGraphType graph, ReductionStats* stats)
		{
			return factorize<RandomGraphType>(std::move(graph), flow_calc, parallel);
		};

		//const reductor_t<RandomGraphType> hanged_vertexes_reduction = std::bind(random_graph_reductions::remove_hanged_vertexes<RandomGraphType>, std::placeholders::_1, std::placeholders::_2, factorization);

		return random_graph_reductions::split_to_components<RandomGraphType>(random_graph, stats, factorization);
    }

    #undef MAKE_REDUCTOR
}
