#ifndef GRAPH_CORE_MATRIX_ITERATOR_HPP
#define GRAPH_CORE_MATRIX_ITERATOR_HPP

#include <utility>

#include "core/macroses.hpp"

namespace graphcpp
{
	class MatrixIterator final
	{
	private:
		msize _i, _j;
		msize _dimension;

	public:
		MatrixIterator();
		explicit MatrixIterator(msize dimension);
		MatrixIterator(msize i, msize j, msize dimension);

		std::pair<msize, msize> operator*() const;

		bool operator==(const MatrixIterator& rhs) const;
		bool operator!=(const MatrixIterator& rhs) const;

		MatrixIterator& operator++();
		MatrixIterator operator++(int);
	};
}
#endif
