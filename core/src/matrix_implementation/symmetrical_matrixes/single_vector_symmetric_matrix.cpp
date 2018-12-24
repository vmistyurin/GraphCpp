#include "core/matrix_implementations/symmetric_matrixes/single_vector_symmetric_matrix.hpp"

#include <cassert>

#include "core/utils/numeric.hpp"

using namespace graphcpp;

SingleVectorSymmetricMatrix::SingleVectorSymmetricMatrix() :
	_dimension(0), _internal_dimension(0)
{
}

SingleVectorSymmetricMatrix::SingleVectorSymmetricMatrix(msize dimension) :
    _dimension(dimension), _internal_dimension(dimension), _matrix(dimension * dimension)
{
}

SingleVectorSymmetricMatrix::SingleVectorSymmetricMatrix(const std::vector<std::vector<mcontent>>& matrix) :
    SingleVectorSymmetricMatrix(matrix.size())
{
    assert(check_symmetrical_matrix(matrix));
    
    for (auto[i, j] : *this)
    {
        set(i, j, matrix[i][j]);
    }
}

SingleVectorSymmetricMatrix::SingleVectorSymmetricMatrix(const SingleVectorSymmetricMatrix& rhs) :
    _dimension(rhs.dimension()), _internal_dimension(rhs.dimension()), _matrix(_dimension * _dimension)
{
    for(auto[i, j] : *this)
    {
        set(i, j, rhs.at(i, j));
    }
}

SingleVectorSymmetricMatrix& SingleVectorSymmetricMatrix::operator=(const SingleVectorSymmetricMatrix& rhs)
{
    _dimension = rhs.dimension();
    _internal_dimension = rhs.dimension();
    _matrix = std::vector<mcontent>(); _matrix.resize(_dimension * _dimension);
    
    for(auto[i, j] : *this)
    {
        set(i, j, rhs.at(i, j));
    }

    return *this;
}

SingleVectorSymmetricMatrix& SingleVectorSymmetricMatrix::operator+=(const SingleVectorSymmetricMatrix& rhs)
{
	assert(dimension() == rhs.dimension());

	for (msize i = 0; i < _internal_dimension * _internal_dimension; i++)
	{
		_matrix[i] += rhs._matrix[i];
	}

    return *this;
}

SingleVectorSymmetricMatrix& SingleVectorSymmetricMatrix::operator*=(double multiplier)
{
	for (msize i = 0; i < _internal_dimension; i++)
	{
		_matrix[i] *= multiplier;
	}

    return *this;
}

msize SingleVectorSymmetricMatrix::dimension() const
{
    return _dimension;
}

mcontent SingleVectorSymmetricMatrix::at(msize index1, msize index2) const
{
    assert(std::max(index1, index2) < dimension());
    
    return _matrix[index1 * _internal_dimension + index2];
}

void SingleVectorSymmetricMatrix::set(msize index1, msize index2, mcontent value)
{
    assert(std::max(index1, index2) < dimension());
    
    _matrix[index1 * _internal_dimension + index2] = value;
    _matrix[index2 * _internal_dimension + index1] = value;
}

void SingleVectorSymmetricMatrix::reduce_element(msize index1, msize index2, mcontent difference)
{
    assert(std::max(index1, index2) < dimension());
    
    _matrix[index1 * _internal_dimension + index2] =  _matrix[index1 * _internal_dimension + index2] - difference;
}

void SingleVectorSymmetricMatrix::rearrange_with_allocate(const std::vector<msize>& new_nums)
{
    assert(new_nums.size() == dimension());
    
    SingleVectorSymmetricMatrix new_matrix(_dimension);
    
    for (auto[i, j] : *this)
    {
        new_matrix.set(new_nums[i], new_nums[j], at(i, j));
    }
    
    _matrix = std::move(new_matrix._matrix);
}

void SingleVectorSymmetricMatrix::swap(msize str1, msize str2)
{
    assert(str1 != str2);
    assert(std::max(str1, str2) < dimension());
    
    const mcontent previous_value = at(str1, str2);
    
    for (msize i = 0; i < dimension(); i++)
    {
        const auto prev = at(i, str1);
        set(i, str1, at(i, str2));
        set(i, str2, prev);
    }

    set(str1, str2, previous_value);
}

void SingleVectorSymmetricMatrix::delete_last_strings(msize count)
{
    assert(count < dimension());
    
    _dimension -= count;
    
    for (msize i = 0; i < _dimension; i++)
    {
        set(i, i, 0);
    }
}

std::unique_ptr<SingleVectorSymmetricMatrix> SingleVectorSymmetricMatrix::with_deleted_vertexes(const std::vector<msize>& vertexes) const
{
    assert(!vertexes.empty());
    assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](auto vertex) { return vertex < dimension(); }));
    
    auto result = std::make_unique<SingleVectorSymmetricMatrix>(dimension() - vertexes.size());
    
    auto new_nums = std::vector<msize>(); new_nums.reserve(dimension() - vertexes.size());
    msize position_in_deleted = 0;
    for (msize i = 0; i < dimension(); i++)
    {
        if (vertexes[position_in_deleted] == i)
        {
            position_in_deleted++;
            continue;
        }
        new_nums.push_back(i);
    }
    
    for (msize i = 0; i < new_nums.size(); i++)
    {
        for (msize j = i + 1; j < new_nums.size(); j++)
        {
            result->set(i, j, at(new_nums[i], new_nums[j]));
        }
    }
    
    return result;
}

std::unique_ptr<SingleVectorSymmetricMatrix> SingleVectorSymmetricMatrix::with_deleted_element(msize i, msize j) const
{
    assert(std::max(i, j) < dimension());
    
    auto result = std::make_unique<SingleVectorSymmetricMatrix>(*this);
    result->set(i, j, 0);
    return result;
}
