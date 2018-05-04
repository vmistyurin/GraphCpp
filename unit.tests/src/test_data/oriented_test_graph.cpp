#include "unit.tests/test_data/oriented_test_graph.hpp"

#include "unit.tests/test_data/tested_matrix.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

namespace
{
	
}

msize oriented_test_graph::dimension()
{
	return tested_matrix::dimension();
}

std::vector<Edge> oriented_test_graph::get_edges()
{
	std::vector<Edge> result;
	for(msize i = 0; i < dimension(); i++)
	{
		for(msize j = 0; j < dimension(); j++)
		{
			if(tested_matrix::matrix_as_vector()[i][j] > 0)
			{
				result.emplace_back(i, j, tested_matrix::matrix_as_vector()[i][j]);
			}
		}
	}

	return result;
}

std::vector<msize> oriented_test_graph::get_degrees()
{
	std::vector<msize> result(dimension());

	for(msize i = 0; i < dimension(); i++)
	{
		for(msize j = 0; j < dimension(); j++)
		{
			if(tested_matrix::matrix_as_vector()[i][j] > 0)
			{
				result[i]++;
			}
		}
	}

	return result;
}

template<>
std::unique_ptr<OrientedMatrixGraph<Matrix>> oriented_test_graph::get_graph<OrientedMatrixGraph<Matrix>>()
{
	return std::make_unique<OrientedMatrixGraph<Matrix>>(tested_matrix::matrix_as_vector());
}