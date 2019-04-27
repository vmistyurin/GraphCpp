#pragma once

#include "core/matrices/symmetric_matrices/symmetric_matrix_base.hpp"

namespace graphcpp
{
    class SingleVectorSymmetricMatrix final: public SymmetricMatrixBase
    {
    private:
        msize _dimension;
        msize _internal_dimension;
        std::vector<mcontent> _matrix;
        
    public:
		SingleVectorSymmetricMatrix() = default;
        explicit SingleVectorSymmetricMatrix(msize dimension);
        explicit SingleVectorSymmetricMatrix(const std::vector<std::vector<mcontent>>& matrix);
        explicit SingleVectorSymmetricMatrix(const SymmetricMatrixBase& matrix);

        SingleVectorSymmetricMatrix(const SingleVectorSymmetricMatrix& rhs) = default;
        SingleVectorSymmetricMatrix& operator=(const SingleVectorSymmetricMatrix& rhs) = default;

        msize dimension() const override;
        mcontent at(msize index1, msize index2) const override;
        void set(msize index1, msize index2, mcontent value) override;
        void reduce_element(msize index1, msize index2, mcontent difference) override;
        
        void rearrange_with_allocate(const std::vector<msize>& new_nums) override;
        
        void swap(msize str1, msize str2) override;
        void delete_last_strings(msize count) override;

        SingleVectorSymmetricMatrix extract_matrix(const std::vector<msize>& rows);
    };
}
