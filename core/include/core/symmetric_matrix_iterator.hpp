#ifndef GRAPH_CORE_SYMMETRIC_MATRIX_ITERATOR_HPP
#define GRAPH_CORE_SYMMETRIC_MATRIX_ITERATOR_HPP

#include "core/macroses.hpp"
#include <utility>

namespace graphcpp
{
	class SymmetricMatrixIterator final
	{
	private:
		msize _i, _j;
		msize _dimension;

	public:
		SymmetricMatrixIterator();
		explicit SymmetricMatrixIterator(msize dimension);
		SymmetricMatrixIterator(msize i, msize j, msize dimension);
		
		std::pair<msize, msize> operator*() const;

		bool operator==(const SymmetricMatrixIterator& rhs) const;
		bool operator!=(const SymmetricMatrixIterator& rhs) const;

		SymmetricMatrixIterator& operator++();
		SymmetricMatrixIterator operator++(int);
	};
}
#endif