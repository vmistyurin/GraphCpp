#ifndef GRAPH_CORE_FULL_SYMMETRIC_MATRIX_HPP
#define GRAPH_CORE_FULL_SYMMETRIC_MATRIX_HPP

#include "core/matrix_implementation/symmetric_matrix_base.hpp"

namespace graphcpp
{
	class FullSymmetricMatrix final: public SymmetricMatrixBase
	{
	private:
		std::vector<std::vector<mcontent>> _matrix;

	public:
		explicit FullSymmetricMatrix(msize dimension);
		explicit FullSymmetricMatrix(const std::vector<std::vector<mcontent>>& matrix);
		explicit FullSymmetricMatrix(const SymmetricMatrixBase& matrix);
		
		bool operator==(const SymmetricMatrixBase& rhs) const override;
		bool operator!=(const SymmetricMatrixBase& rhs) const override;

		msize dimension() const override;
		mcontent at(msize index1, msize index2) const override;
		void set(msize index1, msize index2, mcontent value) override;
		void reduce_element(msize index1, msize index2, mcontent difference) override;
		std::vector<mcontent> get_string(msize str) const override;

		void make_rearranged(const std::vector<msize>& new_nums, std::shared_ptr<SymmetricMatrixBase> memory) const override;
		void rearrange_with_permutations(const std::vector<msize>& new_nums) override;
		void rearrange_with_allocate(const std::vector<msize>& new_nums) override;

		void swap(msize str1, msize str2) override;
		void delete_last_strings(msize count) override;

	private:
		void fill_diagonal(mcontent value = 0);
	};
}
#endif
