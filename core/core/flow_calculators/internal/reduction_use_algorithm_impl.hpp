#pragma once


//namespace
//{
//    msize global_to_chain_number(const std::vector<msize>& chain, msize global_number)
//    {
//        for (msize i = 0; i < chain.size(); i++)
//        {
//            if (chain[i] == global_number)
//            {
//                return i;
//            }
//        }
//
//        abort();
//    }
//
//    std::unique_ptr<SymmetricMatrixBase> shrink_chains(NonOrientedGraphBase& graph, std::vector<std::vector<msize>>& chains, const single_flow_function& single_flow_calculator)
//    {
//        RETURN_IF(chains.empty(), remove_hanged_vertexes(graph, single_flow_calculator));
//
//        auto result = std::make_unique<SymmetricMatrixType>(graph.dimension());
//
//        auto chain = std::move(chains.back());
//        chains.pop_back();
//
//        auto capacity = mcontent_undefined;
//        auto new_num = msize_undefined;
//        for (msize i = 0; i < chain.size() - 1; i++)
//        {
//            capacity = std::min(capacity, graph.at(chain[i], chain[i + 1]));
//            new_num = std::min(new_num, chain[i]);
//        }
//
//        auto left_chain_element = chain.front();
//        auto right_chain_element = chain.back();
//
//        chain.pop_back();
//        chain.erase(chain.begin());
//
//        std::vector<mcontent> left_flows(chain.size());
//        auto left_flow = graph.at(left_chain_element, chain.front());
//        for (msize i = 0; i < chain.size() - 1; i++)
//        {
//            left_flows[i] = left_flow;
//            left_flow = std::min(left_flow, graph.at(chain[i], chain[i + 1]));
//        }
//
//        std::vector<mcontent> right_flows(chain.size());
//        auto right_flow = graph.at(right_chain_element, chain.back());
//        for (msize i = chain.size() - 1; i > 0; i--)
//        {
//            right_flows[i] = right_flow;
//            right_flow = std::min(right_flow, graph.at(chain[i], chain[i - 1]));
//        }
//
//        auto new_nums = graph.delete_vertexes(chain);
//        graph.set(new_nums[left_chain_element], new_nums[right_chain_element], graph.at(new_nums[left_chain_element], new_nums[right_chain_element]) + capacity);
//
//        for (auto& chain : chains)
//        {
//            for(msize i = 0; i < chain.size(); i++)
//            {
//                chain[i] = new_nums[chain[i]];
//            }
//        }
//
//        auto subgraph_flows = shrink_chains(graph, chains, single_flow_calculator);
//
//        for(auto[i, j] : *result)
//        {
//            if (new_nums[i] != msize_undefined && new_nums[j] != msize_undefined)
//            {
//                result->set(i, j, subgraph_flows->at(new_nums[i], new_nums[j]));
//            }
//            else if (new_nums[i] == msize_undefined && new_nums[j] == msize_undefined)
//            {
//                result->set(i, j, std::fabs(right_flows[global_to_chain_number(chain, i)] - right_flows[global_to_chain_number(chain, j)]));
//            }
//            else if (new_nums[i] != msize_undefined)
//            {
//                auto flow = std::min(subgraph_flows->at(new_nums[i], new_nums[left_chain_element]), left_flows[global_to_chain_number(chain, j)]) +
//                std::min(subgraph_flows->at(new_nums[i], new_nums[right_chain_element]), right_flows[global_to_chain_number(chain, j)]);
//
//                result->set(i, j, flow);
//            }
//            else if (new_nums[j] != msize_undefined)
//            {
//                auto flow = std::min(subgraph_flows->at(new_nums[j], new_nums[left_chain_element]), left_flows[global_to_chain_number(chain, i)]) +
//                std::min(subgraph_flows->at(new_nums[j], new_nums[right_chain_element]), right_flows[global_to_chain_number(chain, i)]);
//
//                result->set(i, j, flow);
//            }
//        }
//
//        return result;
//    }
//
//    std::unique_ptr<SymmetricMatrixBase> parse_chains(NonOrientedGraphBase& graph, const single_flow_function& single_flow_calculator)
//    {
//        auto chains = graph.get_chains();
//        return shrink_chains(graph, chains, single_flow_calculator);
//    }
//}
//