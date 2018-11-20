#pragma once

#include "core/macroses.hpp"
#include "core/utils.hpp"

#include "core/edges/edge.hpp"
#include "core/edges/symmetric_edge.hpp"
#include "core/edges/random_edge.hpp"
#include "core/edges/symmetric_random_edge.hpp"

#include "core/iterators/matrix_iterator.hpp"
#include "core/iterators/symmetric_matrix_iterator.hpp"

#include "core/matrix_implementations/matrix_base.hpp"
#include "core/matrix_implementations/matrix_implementations.hpp"

#include "core/matrix_implementations/non-symmetric_matrixes/non-symmetric_matrix_base.hpp"
#include "core/matrix_implementations/non-symmetric_matrixes/matrix.hpp"
#include "core/matrix_implementations/non-symmetric_matrixes/single_vector_matrix.hpp"

#include "core/graph_implementations/graph_base.hpp"
#include "core/graph_implementations/matrix_graph.hpp"

#include "core/graph_implementations/non-oriented_graphs/non_oriented_graph_base.hpp"
#include "core/graph_implementations/non-oriented_graphs/non_oriented_matrix_graph.hpp"

#include "core/graph_implementations/oriented_graphs/oriented_graph_base.hpp"
#include "core/graph_implementations/oriented_graphs/oriented_matrix_graph.hpp"

#include "core/random_graph_implementations/random_graph_base.hpp"
#include "core/random_graph_implementations/non_oriented_graphs/random_non_oriented_graph_base.hpp"
#include "core/random_graph_implementations/non_oriented_graphs/random_non_oriented_graph.hpp"

#include "core/flow_calculators.hpp"

#include "core/computations/summator.hpp"
#include "core/computations/single_threaded/single_thread_summator.hpp"
#include "core/computations/single_threaded/single_thread_calculator.hpp"
#include "core/computations/multi_threaded/multi_thread_summator.hpp"
#include "core/computations/multi_threaded/multi_thread_calculator.hpp"

#include "core/utils/thread_pool.hpp"
