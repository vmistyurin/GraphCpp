#pragma once

#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"

namespace graphcpp
{
	class FullSymmetricMatrix final: public SymmetricMatrixBase<FullSymmetricMatrix>
	{
	private:
		std::vector<std::vector<mcontent>> _matrix;

	public:
		FullSymmetricMatrix() = default;
		explicit FullSymmetricMatrix(msize dimension);
		explicit FullSymmetricMatrix(const std::vector<std::vector<mcontent>>& matrix);
        
        template<class RhsImplType>
		explicit FullSymmetricMatrix(const SymmetricMatrixBase<RhsImplType>& rhs);
		
		msize dimension() const;
		mcontent at(msize index1, msize index2) const;
		void set(msize index1, msize index2, mcontent value);
		void reduce_element(msize index1, msize index2, mcontent difference);

		void rearrange_with_allocate(const std::vector<msize>& new_nums);

		void swap(msize str1, msize str2);
		void delete_last_strings(msize count);

		std::unique_ptr<FullSymmetricMatrix> with_deleted_vertexes(const std::vector<msize>& vertexes) const;
		std::unique_ptr<FullSymmetricMatrix> with_deleted_element(msize i, msize j) const;
	};
    
    template<class RhsImplType>
    FullSymmetricMatrix::FullSymmetricMatrix(const SymmetricMatrixBase<RhsImplType>& rhs) :
        FullSymmetricMatrix(rhs.dimension())
    {
        for (auto[i, j] : rhs)
        {
            set(i, j, rhs.at(i, j));
        }
    }
}
