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

using RandomGraphImplementations = testing::Types<
	graphcpp::RandomGraph<graphcpp::NonOrientedMatrixGraph<graphcpp::FullSymmetricMatrix>>,
	graphcpp::RandomGraph<graphcpp::OrientedMatrixGraph<graphcpp::Matrix>>
>;

#endif