#pragma once

#include "core/matrices/non_symmetric_matrices/non_symmetric_matrix_base.hpp"

namespace graphcpp
{
    class SingleVectorMatrix final: public NonSymmetricMatrixBase
    {
    private:
        msize _dimension;
        msize _internal_dimension;
        std::vector<mcontent> _matrix;
        
    public:
        explicit SingleVectorMatrix(msize dimension);
        explicit SingleVectorMatrix(const std::vector<std::vector<mcontent>>& matrix);
        explicit SingleVectorMatrix(const MatrixBase& rhs);
        
        SingleVectorMatrix(const SingleVectorMatrix& rhs);
        SingleVectorMatrix& operator=(const SingleVectorMatrix& rhs);
        
        msize dimension() const override;
        mcontent at(msize index1, msize index2) const override;
        void set(msize index1, msize index2, mcontent value) override;
        void reduce_element(msize index1, msize index2, mcontent difference) override;
        
        void rearrange_with_allocate(const std::vector<msize>& new_nums) override;
        
        void swap(msize str1, msize str2) override;
        void delete_last_strings(msize count) override;        
    };
}
