#ifndef GRAPH_CORE_MATRIX
#define GRAPH_CORE_MATRIX

#include "MatrixImplementation/matrix_base.h"

namespace graphcpp
{
	class Matrix : public MatrixBase
	{
	private:
		std::vector<std::vector<bool>> _matrix;
	public:
		explicit Matrix(ushort dimension);
		explicit Matrix(const std::vector<std::vector<bool>>& matrix);

		bool operator==(const MatrixBase& right) const override;
		bool operator!=(const MatrixBase& right) const override;

		void swap(ushort str1, ushort str2) override;
		const std::vector<bool>& get_string(ushort str) const override;
		bool at(ushort index1, ushort index2) const override;
		ushort dimension() const override;
	};
}
#endif
