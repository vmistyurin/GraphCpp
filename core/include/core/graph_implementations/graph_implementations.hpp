#ifndef GRAPH_CORE_GRAPH_IMPLEMENTATIONS_HPP
#define GRAPH_CORE_GRAPH_IMPLEMENTATIONS_HPP

#include "core/graph_implementations/matrix_graph.hpp"
#include "core/matrix_implementations/matrix_implementations.hpp"

#define GRAPH_IMPLEMENTATIONS_SEQ (graphcpp::MatrixGraph<graphcpp::FullSymmetricMatrix>) (graphcpp::MatrixGraph<graphcpp::HalfSymmetricMatrix>)

//TODO : uncomment and fix this
//#define GRAPH_IMPLEMENTATIONS_MATRIX_GRAPH(matrix_type) graphcpp::MatrixGraph<matrix_type>
//#define GRAPH_IMPLEMENTATIONS_MATRIX_GRAPH_MACRO(r, data, matrix_type) BOOST_PP_SEQ_PUSH_BACK(GRAPH_IMPLEMENTATIONS_SEQ, GRAPH_IMPLEMENTATIONS_MATRIX_GRAPH(matrix_type))
//BOOST_PP_SEQ_FOR_EACH(GRAPH_IMPLEMENTATIONS_MATRIX_GRAPH_MACRO, 0, MATRIX_IMPLEMENTATIONS_SEQ)

#endif
