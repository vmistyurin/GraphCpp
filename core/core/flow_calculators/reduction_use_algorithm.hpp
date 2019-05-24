#pragma once

#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/reduction_stats.hpp"

#include "core/flow_calculators/reductions/calculate_if_tree.hpp"
#include "core/flow_calculators/reductions/remove_connected_trees_reduction.hpp"
#include "core/flow_calculators/reductions/remove_hanged_vertexes_reduction.hpp"
#include "core/flow_calculators/reductions/split_to_components_reduction.hpp"
#include "core/flow_calculators/reductions/bridge_reduction.hpp"
//#include "core/flow_calculators/reductions/hinge_reduction.hpp"
//#include "core/flow_calculators/reductions/chains_reductions.hpp"

namespace graphcpp::flow_calculators
{
    #define MAKE_REDUCTOR(function_name, next_reductor) std::bind(function_name<SymMatrixType, NorGraphType>, std::placeholders::_1, std::placeholders::_2, next_reductor) 

    template<class NorGraphType, class SymMatrixType>
    SymMatrixType reduction_use_algorithm(
        const NorGraphType& graph,
        flow_func_t<SymMatrixType, NorGraphType> flow_calc,
        ReductionStats* stats
    )
    {
        using namespace graphcpp::flow_calculators::reductors;
        using reductor_type = std::function<SymMatrixType(NorGraphType, ReductionStats*)>;
        
        const reductor_type matrix_of_flows = std::bind(std::move(flow_calc), std::placeholders::_1);
        const reductor_type reduce_connected_trees = MAKE_REDUCTOR(remove_connected_trees, matrix_of_flows);
		const reductor_type bridge_reduction = MAKE_REDUCTOR(reductors::bridge_reduction, reduce_connected_trees);
		//const reductor_type hinge_reduction = MAKE_REDUCTOR(hinge_reductions, bridge_reduction);
		//const reductor_type chains_reduction = MAKE_REDUCTOR(chains_reductions, bridge_reduction);
		const reductor_type reduce_hanged_vertexes = MAKE_REDUCTOR(remove_hanged_vertexes, bridge_reduction);
        const reductor_type check_trees = MAKE_REDUCTOR(calculate_if_tree, reduce_hanged_vertexes);
        
        return split_to_components(graph, stats, check_trees);
    }
    
    #undef MAKE_REDUCTOR
    
    template<class NorGraphType, class SymMatrixType>
    SymMatrixType reduction_use_algorithm(
        const NorGraphType& graph,
        single_flow_function_t<NorGraphType> flow_calc,
        ReductionStats* stats
    )
    {
        flow_func_t<SymMatrixType, NorGraphType> matrix_of_flows = std::bind(
            flow_calculators::matrix_of_flows<SymMatrixType, NorGraphType>,
            std::placeholders::_1,
            std::move(flow_calc)
        );

        return reduction_use_algorithm<NorGraphType, SymMatrixType>(graph, matrix_of_flows, stats);
    }
}
