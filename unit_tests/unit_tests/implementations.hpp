#pragma once

#include "gtest/gtest.h"

#include "core/matrices/non_symmetric_matrices/matrix.hpp"
#include "core/matrices/non_symmetric_matrices/single_vector_matrix.hpp"
#include "core/matrices/symmetric_matrices/full_symmetric_matrix.hpp"
#include "core/matrices/symmetric_matrices/half_symmetric_matrix.hpp"
#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/graphs/non_oriented_graphs/non_oriented_matrix_graph.hpp"
#include "core/graphs/oriented_graphs/oriented_matrix_graph.hpp"
#include "core/random_graphs/non_oriented_graphs/random_non_oriented_graph.hpp"

namespace graphcpp_testing
{
    using MatrixImplementations = testing::Types<
        graphcpp::Matrix,
        graphcpp::SingleVectorMatrix
    >;

    using SymmetricMatrixImplementations = testing::Types<
        graphcpp::FullSymmetricMatrix,
        graphcpp::HalfSymmetricMatrix,
        graphcpp::SingleVectorSymmetricMatrix
    >;

    using NonOrientedGraphImplementations = testing::Types<
        graphcpp::NonOrientedMatrixGraph<graphcpp::FullSymmetricMatrix>,
        graphcpp::NonOrientedMatrixGraph<graphcpp::HalfSymmetricMatrix>,
        graphcpp::NonOrientedMatrixGraph<graphcpp::SingleVectorSymmetricMatrix>
    >;

    using OrientedGraphImplementations = testing::Types<
        graphcpp::OrientedMatrixGraph<graphcpp::Matrix>,
        graphcpp::OrientedMatrixGraph<graphcpp::SingleVectorMatrix>
    >;

    using RandomNonOrientedGraphImplementations = testing::Types<
        graphcpp::RandomNonOrientedGraph<graphcpp::NonOrientedMatrixGraph<graphcpp::FullSymmetricMatrix>, graphcpp::HalfSymmetricMatrix>,
        graphcpp::RandomNonOrientedGraph<graphcpp::NonOrientedMatrixGraph<graphcpp::HalfSymmetricMatrix>, graphcpp::SingleVectorSymmetricMatrix>,
        graphcpp::RandomNonOrientedGraph<graphcpp::NonOrientedMatrixGraph<graphcpp::SingleVectorSymmetricMatrix>, graphcpp::SingleVectorSymmetricMatrix>
    >;
}