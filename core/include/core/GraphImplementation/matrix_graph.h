#ifndef GRAPH_CORE_MATRIX_GRAPH_H
#define GRAPH_CORE_MATRIX_GRAPH_H

#include "core/MatrixImplementation/symmetric_matrix_base.h"
#include "core/MatrixImplementation/matrix.h"
#include "graph_base.h"
#include "core/macroses.h"
#include <algorithm>
#include <numeric>

namespace graphcpp
{
	template<class SymmetricMatrixType = Matrix> class MatrixGraph final : public GraphBase
	{
	private:
		SymmetricMatrixType _matrix;

	public:
		MatrixGraph() :
			_matrix(0)
		{}

		explicit MatrixGraph(const std::vector<Edge>& edges, msize dimension) :
			_matrix(dimension)
		{
			for (const auto& edge : edges)
			{
				assert(std::max(edge.v1(), edge.v2()) < dimension);
				_matrix.set(edge.v1(), edge.v2(), edge.weight());
			}
		}

		explicit MatrixGraph(const GraphBase& other) :
			_matrix(other.get_matrix())
		{}

		msize dimension() const override
		{
			return _matrix.dimension();
		}

		bool equal(const GraphBase& other) const override //TODO: Optimize, maybe add weight check
		{
			RETURN_IF(this == &other, true);
			RETURN_IF(dimension() != other.dimension(), false);

			auto this_degrees = get_degrees();
			auto other_degrees = other.get_degrees();
			RETURN_IF(!std::is_permutation(this_degrees.cbegin(), this_degrees.cend(), other_degrees.cbegin()), false);

			std::vector<msize> permutation(dimension());
			std::iota(permutation.begin(), permutation.end(), 0);

			MatrixGraph other_copy(other);
			do
			{
				other_copy.rearrange(permutation);
				RETURN_IF(_matrix == other_copy.get_matrix(), true);
			} while (std::next_permutation(permutation.begin(), permutation.end()));

			return false;
		}

		const SymmetricMatrixBase& get_matrix() const override
		{
			return _matrix;
		}

		std::vector<Edge> get_edges() const override
		{
			std::vector<Edge> result;
			for (msize i = 0; i < dimension(); i++)
			{
				for (msize j = 0; j < i; j++)
				{
					if (_matrix.at(i, j) != 0)
					{
						result.emplace_back(i, j, _matrix.at(i, j));
					}
				}
			}
			return result;
		}

		std::vector<msize> get_linked_vertexes(msize vertex) const override
		{
			assert(vertex < dimension());

			std::vector<msize> result;
			auto string = _matrix.get_string(vertex);
			for (msize i = 0; i < dimension(); i++)
			{
				if (string[i] != 0 && i != vertex)
				{
					result.push_back(i);
				}
			}
			return result;
		}

        std::vector<msize> get_degrees() const override
        {
			std::vector<msize> result; result.reserve(dimension());
            for(const auto& str : _matrix)
            {
                msize current_degree = 0;
                for(auto value : str)
                {
                    if(value > 0) //TODO: test mask
                    {
                        current_degree++;
                    }
                }
                result.push_back(current_degree);
            }
            return result;
        }

		msize get_degree(msize vertex) const override
		{
			assert(vertex < dimension());

			msize result = 0;
			for(auto value : _matrix.get_string(vertex))
			{
				if(value > 0)
				{
					result++;
				}
			}
			return result;
		}

		void delete_vertexes(const std::vector<msize>& vertexes) override
		{
			assert(!vertexes.empty());
			assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](msize vertex){return vertex < dimension();}));

			std::set<msize> to_delete(vertexes.cbegin(), vertexes.cend());
			msize current_position = dimension() - 1;
			for (auto current_deleted : to_delete)
			{
				while (to_delete.count(current_position) == 1)
				{
					to_delete.erase(current_position);
					current_position--;
				}
				_matrix.swap(current_position, current_deleted);
				current_position--;
			}
			_matrix.delete_last_strings(vertexes.size());
		}

		void rearrange(const std::vector<msize>& new_nums) override
		{
			_matrix.rearrange(new_nums);
		}
	};
}
#endif