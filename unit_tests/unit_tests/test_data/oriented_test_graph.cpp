#include "unit_tests/test_data/oriented_test_graph.hpp"

#include "unit_tests/test_data/test_matrix.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

msize oriented_test_graph::dimension()
{
	return test_matrix::dimension();
}

std::vector<Edge> oriented_test_graph::get_edges()
{
	std::vector<Edge> result;
	for(msize i = 0; i < dimension(); i++)
	{
		for(msize j = 0; j < dimension(); j++)
		{
			if(test_matrix::matrix_as_vector()[i][j] > 0)
			{
				result.emplace_back(i, j, test_matrix::matrix_as_vector()[i][j]);
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
			if(test_matrix::matrix_as_vector()[i][j] > 0)
			{
				result[i]++;
			}
		}
	}

	return result;
}
