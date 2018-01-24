#ifndef GRAPH_CORE_MATRIX_H
#define GRAPH_CORE_MATRIX_H

#include "symmetric_matrix_base.h"
#include <algorithm>
#include <assert.h>
#include <numeric>

namespace graphcpp
{
	class Matrix final: public SymmetricMatrixBase
	{
	private:
		std::vector<std::vector<mcontent>> _matrix;

	public:
		explicit Matrix(msize dimension)
		{
			_matrix.resize(dimension);
			for (auto& str : _matrix)
			{
				str.resize(dimension);
			}
		}

		explicit Matrix(const std::vector<std::vector<mcontent>>& matrix) : Matrix(matrix.size())
		{
			assert(matrix.size() < std::numeric_limits<msize>::max());
            for(msize i = 0; i < matrix.size(); i++)
            {
                assert(matrix[i].size() == matrix.size());
            }
			for (msize i = 0; i < matrix.size(); i++)
			{
				for (msize j = 0; j < matrix.size(); j++)
				{
					_matrix[i][j] = matrix[i][j];
				}
			}
            fill_diagonal();
		}

		explicit Matrix(const SymmetricMatrixBase& matrix)
		{
			_matrix.resize(matrix.dimension());
			for (msize i = 0; i < dimension(); i++)
			{
				_matrix[i] = matrix.get_string(i);
			}
		}
		
		bool operator==(const SymmetricMatrixBase& right) const override
		{
            RETURN_IF(this == &right, true);
            RETURN_IF(right.dimension() != dimension(), false);
			for (msize i = 0; i < dimension(); i++)
			{
                RETURN_IF(get_string(i) != right.get_string(i), false);
			}
			return true;
		}

		bool operator!=(const SymmetricMatrixBase& right) const override
		{
			return !(*this == right);
		}

		msize dimension() const override
		{
			return _matrix.size();
		}

		mcontent at(msize index1, msize index2) const override
		{
			assert(std::max(index1, index2) < dimension());

			return _matrix[index1][index2];
		}

		void set(msize index1, msize index2, mcontent value) override
		{
			assert(index1 != index2);
			assert(std::max(index1, index2) < dimension());

			_matrix[index1][index2] = value;
			_matrix[index2][index1] = value;
		}

		const std::vector<mcontent>& get_string(msize str) const override
		{
			assert(str < dimension());

			return _matrix[str];
		}

		void swap(msize str1, msize str2) override //Todo: optimize
		{
			assert(str1 != str2);
			assert(std::max(str1, str2) < dimension());

			const mcontent previous_value = _matrix[str1][str2];

			std::swap(_matrix[str1], _matrix[str2]);

			for (msize i = 0; i < dimension(); i++)
			{
				std::swap(_matrix[i][str1], _matrix[i][str2]);
			}

			_matrix[str1][str2] = previous_value;
			_matrix[str2][str1] = previous_value;
		}

		void rearrange(const std::vector<msize>& new_nums) override
		{
			std::vector<int> const_permatation; const_permatation.resize(dimension());
			std::iota(const_permatation.begin(), const_permatation.end(), 0);
			assert(std::is_permutation(new_nums.cbegin(), new_nums.cend(), const_permatation.cbegin(), const_permatation.cend()));

			Matrix result(dimension());
			for (msize i = 0; i < dimension(); i++)
			{
				for (msize j = i + 1; j < dimension(); j++)
				{
					result.set(new_nums[i], new_nums[j], _matrix[i][j]);
				}
			}
			_matrix = std::move(result._matrix);
		}

		virtual void delete_last_strings(msize count) //TODO: make it better
		{
			assert(count <= dimension());

			for (msize i = 0; i < count; i++)
			{
				_matrix.pop_back();
			}
			for (msize i = 0; i < dimension(); i++)
			{
				for (msize j = 0; j < count; j++)
				{
					_matrix[i].pop_back();
				}
			}
		}
		
	    std::vector<std::vector<mcontent>>::const_iterator begin() const override
		{
			return _matrix.cbegin();
		}

		std::vector<std::vector<mcontent>>::const_iterator end() const override
        {
            return _matrix.cend();
        }
	private:
		void fill_diagonal(mcontent value = 0)
		{
			for(msize i = 0; i < dimension(); i++)
			{
				_matrix[i][i] = value;
			}
		}
	};
}
#endif
