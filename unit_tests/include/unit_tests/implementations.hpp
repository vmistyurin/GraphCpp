#pragma once

#include "gtest/gtest.h"

#include "core/all.hpp"

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
