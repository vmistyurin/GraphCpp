#ifndef GRAPH_CORE_ALL_HPP
#define GRAPH_CORE_ALL_HPP

#include "core/macroses.hpp"
#include "core/utils.hpp"

#include "core/edges/edge.hpp"
#include "core/edges/symmetrical_edge.hpp"
#include "core/edges/random_edge.hpp"

#include "core/iterators/matrix_iterator.hpp"
#include "core/iterators/symmetric_matrix_iterator.hpp"

#include "core/matrix_implementations/matrix_base.hpp"
#include "core/matrix_implementations/matrix_implementations.hpp"

#include "core/matrix_implementations/non-symmetric_matrixes/non-symmetric_matrix_base.hpp"
#include "core/matrix_implementations/non-symmetric_matrixes/matrix.hpp"

#include "core/graph_implementations/graph_base.hpp"
#include "core/graph_implementations/matrix_graph.hpp"

#include "core/graph_implementations/non-oriented_graphs/non_oriented_graph_base.hpp"
#include "core/graph_implementations/non-oriented_graphs/non_oriented_matrix_graph.hpp"

#include "core/graph_implementations/oriented_graphs/oriented_graph_base.hpp"
#include "core/graph_implementations/oriented_graphs/oriented_matrix_graph.hpp"

#include "core/random_graphs_implementations/random_graph_base.hpp"
#include "core/random_graphs_implementations/random_graph.hpp"

#include "core/flow_calculators.hpp"

#endif
