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

namespace graphcpp::testing
{
    using MatrixImplementations = ::testing::Types<
        Matrix,
        SingleVectorMatrix
    >;

    using SymmetricMatrixImplementations = ::testing::Types<
        FullSymmetricMatrix,
        HalfSymmetricMatrix,
        SingleVectorSymmetricMatrix
    >;

    using NonOrientedGraphImplementations = ::testing::Types<
        NonOrientedMatrixGraph<FullSymmetricMatrix>,
        NonOrientedMatrixGraph<HalfSymmetricMatrix>,
        NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>
    >;

    using OrientedGraphImplementations = ::testing::Types<
        OrientedMatrixGraph<Matrix>,
        OrientedMatrixGraph<SingleVectorMatrix>
    >;

    using RandomNonOrientedGraphImplementations = ::testing::Types<
        RandomNonOrientedGraph<NonOrientedMatrixGraph<FullSymmetricMatrix>, HalfSymmetricMatrix>,
        RandomNonOrientedGraph<NonOrientedMatrixGraph<HalfSymmetricMatrix>, SingleVectorSymmetricMatrix>,
        RandomNonOrientedGraph<NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, SingleVectorSymmetricMatrix>
    >;
}