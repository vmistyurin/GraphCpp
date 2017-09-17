#ifndef GRAPH_CORE_SYMMETRIC_MATRIX
#define GRAPH_CORE_SYMMETRIC_MATRIX 

#include <vector>

namespace graphcpp
{
	class SymmetricMatrix
	{
	private:
		std::vector<std::vector<bool>> _matrix;
	public:
		SymmetricMatrix(unsigned int dimension);
		template <unsigned int N> SymmetricMatrix(std::array<std::array<bool, N>, N> matrix) : SymmetricMatrix(N)
		{
			for (unsigned int i = 0; i < N; i++)
			{
				for (unsigned int j = 0; j < i; j++)
				{
					_matrix[i][j] = matrix[i][j];
				}
			}
		}

		bool at(unsigned int index1, unsigned int index2);
		unsigned int dimension() const;
	};
}
#endif