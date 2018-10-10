#ifndef UNIT_TESTS_IMPLEMENTATIONS_HPP
#define UNIT_TESTS_IMPLEMENTATIONS_HPP

#include "gtest/gtest.h"

#include "core/all.hpp"

using MatrixImplementations = testing::Types<graphcpp::Matrix>;

using SymmetricMatrixImplementations = testing::Types<
	graphcpp::FullSymmetricMatrix,
	graphcpp::HalfSymmetricMatrix
>;

using NonOrientedGraphImplementations = testing::Types<
	graphcpp::NonOrientedMatrixGraph<graphcpp::FullSymmetricMatrix>,
	graphcpp::NonOrientedMatrixGraph<graphcpp::HalfSymmetricMatrix>
>;

using OrientedGraphImplementations = testing::Types<
	graphcpp::OrientedMatrixGraph<graphcpp::Matrix>
>;

using RandomNonOrientedGraphImplementations = testing::Types<
	graphcpp::RandomNonOrientedGraph<graphcpp::NonOrientedMatrixGraph<graphcpp::FullSymmetricMatrix>, graphcpp::FullSymmetricMatrix>,
	graphcpp::RandomNonOrientedGraph<graphcpp::NonOrientedMatrixGraph<graphcpp::HalfSymmetricMatrix>, graphcpp::HalfSymmetricMatrix>
>;

#endif