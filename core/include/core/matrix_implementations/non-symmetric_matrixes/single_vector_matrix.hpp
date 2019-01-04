#pragma once

#include "core/matrix_implementations/non-symmetric_matrixes/non-symmetric_matrix_base.hpp"

#include "boost/pool/pool_alloc.hpp"

namespace graphcpp
{
    class SingleVectorMatrix final: public NonSymmetricMatrixBase<SingleVectorMatrix>
    {
    private:
        msize _dimension;
        msize _internal_dimension;
        std::vector<mcontent> _matrix;
        
    public:
        explicit SingleVectorMatrix(msize dimension);
        explicit SingleVectorMatrix(const std::vector<std::vector<mcontent>>& matrix);
        
        template<class MatrixImpl>
        explicit SingleVectorMatrix(const MatrixImpl& rhs);
        
        SingleVectorMatrix(const SingleVectorMatrix& rhs);
        SingleVectorMatrix& operator=(const SingleVectorMatrix& rhs);
        
        msize dimension() const;
        mcontent at(msize index1, msize index2) const;
        void set(msize index1, msize index2, mcontent value);
        void reduce_element(msize index1, msize index2, mcontent difference);
        
        void rearrange_with_allocate(const std::vector<msize>& new_nums);
        
        void swap(msize str1, msize str2);
        void delete_last_strings(msize count);
    };
    
    template<class MatrixImpl>
    SingleVectorMatrix::SingleVectorMatrix(const MatrixImpl& rhs) :
		SingleVectorMatrix(rhs.dimension())
    {
        for(auto[i, j] : *this)
        {
            set(i, j, rhs.at(i, j));
        }
    }
}
