#ifndef GRAPH_CORE_HALF_SYMMETRIC_MATRIX_H
#define GRAPH_CORE_HALF_SYMMETRIC_MATRIX_H

#include "core/MatrixImplementation/symmetric_matrix_base.h"

namespace graphcpp
{
	class HalfSymmetricMatrix final: public SymmetricMatrixBase
	{
	private:
		std::vector<std::vector<mcontent>> _matrix;

	public:
		explicit HalfSymmetricMatrix(msize dimension);
		explicit HalfSymmetricMatrix(const std::vector<std::vector<mcontent>>& matrix);
		explicit HalfSymmetricMatrix(const SymmetricMatrixBase& matrix);

		bool operator==(const SymmetricMatrixBase& rhs) const override;
		bool operator!=(const SymmetricMatrixBase& rhs) const override;

		msize dimension() const override;
		mcontent at(msize index1, msize index2) const override;
		void set(msize index1, msize index2, mcontent value) override;
		void reduce_element(msize index1, msize index2, mcontent difference) override;
		std::vector<mcontent> get_string(msize str) const override;
		void swap(msize str1, msize str2) override;
		void rearrange(const std::vector<msize>& new_nums) override;
		void delete_last_strings(msize count) override;
	};
}
#endif