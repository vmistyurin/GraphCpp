#ifndef GRAPH_CORE_HALF_SYMMETRIC_MATRIX_H
#define GRAPH_CORE_HALF_SYMMETRIC_MATRIX_H

#include "core/MatrixImplementation/symmetric_matrix_base.h"
#include "core/macroses.h"
#include "core/utils.h"
#include <assert.h>
#include <algorithm>

namespace graphcpp
{
	class HalfSymmetricMatrix final: public SymmetricMatrixBase
	{
	private:
		std::vector<std::vector<mcontent>> _matrix;

	public:
		explicit HalfSymmetricMatrix(msize dimension)
		{
			assert(dimension != 0);

			_matrix.resize(dimension - 1);
			for (msize i = 0; i < dimension - 1; i++)
			{
				_matrix[i].resize(i + 1);
			}
		}

		explicit HalfSymmetricMatrix(const std::vector<std::vector<mcontent>>& matrix) : HalfSymmetricMatrix(matrix.size())
		{
			assert(check_symmetrical_matrix(matrix));
			
			for (msize i = 0; i < dimension(); i++)
			{
				for (msize j = 0; j < i; j++)
				{
					_matrix[i-1][j] = matrix[i][j];
				}
			}
		}

		bool operator==(const SymmetricMatrixBase& rhs) const override
		{
			RETURN_IF(this == &rhs, true);
			RETURN_IF(rhs.dimension() != dimension(), false);
			for (msize i = 1; i < dimension(); i++)
			{
				for (msize j = 0; j < i; j++)
				{
					RETURN_IF(_matrix[i - 1][j] != rhs.at(i, j), false);
				}
			}
			return true;
		}

		bool operator!=(const SymmetricMatrixBase& rhs) const override
		{
			return !(*this == rhs);
		}

		msize dimension() const override
		{
			return _matrix.size() + 1;
		}

		mcontent at(msize index1, msize index2) const override
		{
			auto[index1, index2] = std::minmax(index1, index2);
			assert(index2 < dimension());

			RETURN_IF(index1 == index2, 0);

			return _matrix[index2 - 1][index1];
		}

		void set(msize index1, msize index2, mcontent value) override
		{
			auto[index1, index2] = std::minmax(index1, index2);
			assert(index1 != index2);
			assert(std::max(index1, index2) < dimension());

			_matrix[index2 - 1][index1] = value;
		}

		std::vector<mcontent> get_string(msize str) const override
		{
			assert(str < dimension());

			std::vector<mcontent> result; 
			result.reserve(dimension());
			for (msize i = 0; i < dimension(); i++)
			{
				result.push_back(at(i, str));
			}

			return result;
		}

		void swap(msize str1, msize str2) override
		{
			auto[str1, str2] = std::minmax(str1, str2);
			assert(str1 != str2);
			assert(str2 < dimension());

			for (msize i = 0; i < str1; i++)
			{
				std::swap(_matrix[str1 - 1][i], _matrix[str2 - 1][i]);
			}

			for (msize i = str1 + 1; i < str2; i++)
			{
				std::swap(_matrix[i - 1][str1], _matrix[str2 - 1][i]);
			}

			for (msize i = str2 + 1; i < dimension(); i++)
			{
				std::swap(_matrix[i - 1][str1], _matrix[i - 1][str2]);
			}
		}

		void rearrange(const std::vector<msize>& new_nums) override
		{
			assert(new_nums.size() == dimension());
			assert(is_permutation(new_nums));
			
			auto transpositions = to_transpositions(new_nums);
			for (auto[str1,str2] : transpositions)
			{
				swap(str1, str2);
			}
		}

		void delete_last_strings(msize count)
		{
			for (msize i = 0; i < count; i++)
			{
				_matrix.pop_back();
			}
		}

		std::vector<std::vector<mcontent>>::const_iterator begin() const override
		{
			return std::vector<std::vector<mcontent>>::const_iterator();
		}
		std::vector<std::vector<mcontent>>::const_iterator end() const override
		{
			return std::vector<std::vector<mcontent>>::const_iterator();
		}
	};
}
#endif