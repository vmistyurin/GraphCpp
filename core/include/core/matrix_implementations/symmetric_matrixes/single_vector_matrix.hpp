#pragma once

#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"

namespace graphcpp
{
    class SingleVectorMatrix final: public SymmetricMatrixBase
    {
    private:
        std::vector<mcontent> _matrix;
        msize _dimension;
        
    public:
        explicit SingleVectorMatrix(msize dimension);
        
        msize dimension() const override;
        mcontent at(msize index1, msize index2) const override;
        void set(msize index1, msize index2, mcontent value) override;
        void reduce_element(msize index1, msize index2, mcontent difference) override;
        
        void rearrange_with_permutations(const std::vector<msize>& new_nums) override;
        void rearrange_with_allocate(const std::vector<msize>& new_nums) override;
        
        void swap(msize str1, msize str2) override;
        void delete_last_strings(msize count) override;
        
        std::unique_ptr<SymmetricMatrixBase> with_deleted_vertexes(const std::vector<msize>& vertexes) const override;
        std::unique_ptr<SymmetricMatrixBase> with_deleted_element(msize i, msize j) const override;
    };
}
