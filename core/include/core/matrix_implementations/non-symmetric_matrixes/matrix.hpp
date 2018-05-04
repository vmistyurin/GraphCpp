#ifndef GRAPH_CORE_MATRIX_HPP
#define GRAPH_CORE_MATRIX_HPP

#include "core/matrix_implementations/non-symmetric_matrixes/non-symmetric_matrix_base.hpp"

namespace graphcpp
{
	class Matrix : public NonSymmetricMatrixBase
	{
	private:
		std::vector<std::vector<mcontent>> _matrix;

	public:
		explicit Matrix(msize dimension);
	 	explicit Matrix(std::vector<std::vector<mcontent>> matrix);
		explicit Matrix(const MatrixBase& rhs);

		msize dimension() const override;
		mcontent at(msize index1, msize index2) const override;
		void set(msize index1, msize index2, mcontent value) override;
		void reduce_element(msize index1, msize index2, mcontent difference) override;

		void rearrange_with_permutations(const std::vector<msize>& new_nums) override;
		void rearrange_with_allocate(const std::vector<msize>& new_nums) override;

		void swap(msize str1, msize str2) override;
		void delete_last_strings(msize count) override;

		void make_rearranged(const std::vector<msize>& new_nums, NonSymmetricMatrixBase& memory) const;
	};
}
#endif