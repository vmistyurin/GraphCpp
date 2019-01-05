#pragma once

#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"

#include "boost/pool/pool_alloc.hpp"

namespace graphcpp
{
    class SingleVectorSymmetricMatrix final: public SymmetricMatrixBase<SingleVectorSymmetricMatrix>
    {
    private:
        msize _dimension;
        msize _internal_dimension;
        std::vector<mcontent> _matrix;
        
    public:
		SingleVectorSymmetricMatrix();
        explicit SingleVectorSymmetricMatrix(msize dimension);
        explicit SingleVectorSymmetricMatrix(const std::vector<std::vector<mcontent>>& matrix);
        
        template<class SymMatrixImpl>
        explicit SingleVectorSymmetricMatrix(const SymMatrixImpl& matrix);

        SingleVectorSymmetricMatrix(const SingleVectorSymmetricMatrix& rhs);
        SingleVectorSymmetricMatrix& operator=(const SingleVectorSymmetricMatrix& rhs);

        SingleVectorSymmetricMatrix& operator+=(const SingleVectorSymmetricMatrix& rhs);
        SingleVectorSymmetricMatrix& operator*=(double multiplier);
        
        msize dimension() const;
        mcontent at(msize index1, msize index2) const;
        void set(msize index1, msize index2, mcontent value);
        void reduce_element(msize index1, msize index2, mcontent difference);
        
        void rearrange_with_allocate(const std::vector<msize>& new_nums);
        
        void swap(msize str1, msize str2);
        void delete_last_strings(msize count);
    };
    
    template<class SymMatrixImpl>
    SingleVectorSymmetricMatrix::SingleVectorSymmetricMatrix(const SymMatrixImpl& matrix) :
        SingleVectorSymmetricMatrix(matrix.dimension())
    {
        for (auto[i, j] : *this)
        {
            set(i, j, matrix.at(i, j));
        }
    }
}
