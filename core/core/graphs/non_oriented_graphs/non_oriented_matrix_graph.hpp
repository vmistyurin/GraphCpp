#pragma once

#include <set>
#include <queue>
#include <numeric>

#include "core/utils/numeric.hpp"
#include "core/graphs/non_oriented_graphs/non_oriented_graph_base.hpp"
#include "core/edges/symmetric_edge.hpp"

namespace graphcpp
{
	template<class SymmetricMatrixType>
	class NonOrientedMatrixGraph final: public NonOrientedGraphBase
	{
	protected:
		SymmetricMatrixType _matrix;

	public:
		NonOrientedMatrixGraph(msize dimension = 0);
		NonOrientedMatrixGraph(const std::vector<SymmetricEdge>& edges, msize dimension);
		explicit NonOrientedMatrixGraph(const NonOrientedGraphBase& rhs);
		explicit NonOrientedMatrixGraph(const SymmetricMatrixBase& rhs);

		template<class MatrixType, class Enable = std::enable_if_t<std::is_constructible_v<SymmetricMatrixType, MatrixType>>>
		NonOrientedMatrixGraph(MatrixType&& matrix);

		msize dimension() const override;
		mcontent at(msize v1, msize v2) const override;
		void set(msize v1, msize v2, mcontent value) override;
		void add_vertex() override;

		std::vector<SymmetricEdge> get_edges() const override;
        msize get_number_of_edges() const override;
        
		std::unique_ptr<SymmetricMatrixBase> get_matrix() const override;

		NonOrientedMatrixGraph<SymmetricMatrixType> extract_subgraph(const std::vector<msize>& vertexes) const;

		bool equal(const GraphBase& rhs) const override;

		std::list<std::pair<msize, msize>> get_hanged_vertexes() const override;
		std::vector<msize> get_connected_component(msize vertex) const override;
		std::vector<std::vector<msize>> get_connected_components() const override;
        std::list<std::vector<msize>> get_connected_trees() const override;

		std::vector<msize> delete_vertexes(const std::vector<msize>& vertexes) override;

		void rearrange(const std::vector<msize>& new_nums) override;

		template<class GraphType, class MatrixType>
		GraphType with_deleted_vertexes(const std::vector<msize>& vertexes) const;

		template<class GraphType, class MatrixType>
		GraphType with_deleted_edge(msize i, msize j) const;
	};

	template<class T>
	NonOrientedMatrixGraph<T>::NonOrientedMatrixGraph(msize dimension) : 
		_matrix(dimension)
	{
	}

	template<class T>
	NonOrientedMatrixGraph<T>::NonOrientedMatrixGraph(const std::vector<SymmetricEdge>& edges, msize dimension) :
		_matrix(dimension)
	{
		for (auto edge : edges)
		{
			assert(std::max(edge.v1(), edge.v2()) < dimension);
			set(edge.v1(), edge.v2(), edge.weight);
		}
	}

	template<class T>
	NonOrientedMatrixGraph<T>::NonOrientedMatrixGraph(const NonOrientedGraphBase& other) :
		_matrix(*other.get_matrix())
	{
	}

	template<class T>
	NonOrientedMatrixGraph<T>::NonOrientedMatrixGraph(const SymmetricMatrixBase& rhs) :
		_matrix(rhs)
	{	
	}

	template<class T>
	template<class MatrixType, class Enable>
	NonOrientedMatrixGraph<T>::NonOrientedMatrixGraph(MatrixType&& matrix) :
		_matrix(std::forward<MatrixType>(matrix))
	{
	}

	template<class T>
	msize NonOrientedMatrixGraph<T>::dimension() const
	{
		return _matrix.dimension();
	}

	template<class T>
	mcontent NonOrientedMatrixGraph<T>::at(msize v1, msize v2) const
	{
		assert(std::max(v1, v2) < dimension());

		return _matrix.at(v1, v2);
	}

	template<class T>
	void NonOrientedMatrixGraph<T>::set(msize v1, msize v2, mcontent value)
	{
		assert(std::max(v1, v2) < dimension());

		_matrix.set(v1, v2, value);
	}

	template<class T>
	void NonOrientedMatrixGraph<T>::add_vertex()
	{
		_matrix.add_string();
	}

	template<class T>
	bool NonOrientedMatrixGraph<T>::equal(const GraphBase& rhs) const //TODO: Optimize, maybe add weight check
	{
		RETURN_IF(this == &rhs, true);
		RETURN_IF(dimension() != rhs.dimension(), false);

		auto this_degrees = get_degrees();
		auto other_degrees = rhs.get_degrees();
		RETURN_IF(!std::is_permutation(this_degrees.cbegin(), this_degrees.cend(), other_degrees.cbegin()), false);

		std::vector<msize> permutation(dimension());
		std::iota(permutation.begin(), permutation.end(), 0);

		T this_copy = _matrix;
		do
		{
			_matrix.make_rearranged(permutation, this_copy);
			RETURN_IF(is_matrix_from_graph(this_copy, rhs), true);
		} while (std::next_permutation(permutation.begin(), permutation.end()));

		return false;
	}

	template<class T>
	std::vector<SymmetricEdge> NonOrientedMatrixGraph<T>::get_edges() const
	{
		std::vector<SymmetricEdge> result;
		for (auto[i, j] : *this)
		{
			if (at(i, j) != 0)
			{
				result.emplace_back(i, j, at(i, j));
			}
		}

		return result;
	}

    template<class T>
    msize NonOrientedMatrixGraph<T>::get_number_of_edges() const
    {
        msize result = 0;
        
        for(auto[i, j] : *this)
        {
            if (at(i, j) > 0)
            {
                result++;
            }
        }
        
        return result;
    }

	template<class T> 
	std::unique_ptr<SymmetricMatrixBase> NonOrientedMatrixGraph<T>::get_matrix() const
	{
		return std::make_unique<T>(_matrix);
	}

	template<class T>
	std::list<std::pair<msize, msize>> NonOrientedMatrixGraph<T>::get_hanged_vertexes() const
	{
		std::list<std::pair<msize, msize>> result;

		for (msize i = 0; i < dimension(); i++)
		{
			auto linked_with = get_linked_vertexes(i);
			if (linked_with.size() == 1)
			{
				result.emplace_back(i, linked_with[0]);
			}
		}

		return result;
	}

	template<class T>
	NonOrientedMatrixGraph<T> NonOrientedMatrixGraph<T>::extract_subgraph(const std::vector<msize>& vertexes) const
	{
		assert(!vertexes.empty());
		assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](auto vertex) { return vertex < dimension(); }));

		NonOrientedMatrixGraph<T> result(vertexes.size());
		for (msize i = 0; i < vertexes.size(); i++)
		{
			for (msize j = 0; j < i; j++)
			{
				result.set(i, j, _matrix.at(vertexes[i], vertexes[j]));
			}
		}

		return result;
	}

	template<class T>
	std::vector<msize> NonOrientedMatrixGraph<T>::delete_vertexes(const std::vector<msize>& vertexes)
	{
		assert(!vertexes.empty());
		assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](msize vertex) { return vertex < dimension(); }));

		_matrix.delete_strings(vertexes);
		
		std::vector<msize> new_nums(dimension() + vertexes.size());
		msize current = 0;
		for (msize i = 0; i < new_nums.size(); i++)
		{
			if (contains(vertexes, i))
			{
				new_nums[i] = msize_undefined;
			}
			else
			{
				new_nums[i] = current++;
			}
		}

		return new_nums;
	}

	template<class T>
	void NonOrientedMatrixGraph<T>::rearrange(const std::vector<msize>& new_nums)
	{
		_matrix.rearrange_with_allocate(new_nums);
	}

	template<class T>
	std::vector<msize> NonOrientedMatrixGraph<T>::get_connected_component(msize vertex) const
	{
		assert(vertex < dimension());

		std::set<msize> result;
		std::queue<msize> queue;

		result.insert(vertex);
		queue.push(vertex);

		while (!queue.empty())
		{
			auto current_vertex = queue.front(); queue.pop();
			for (msize i = 0; i < dimension(); i++)
			{
				if (_matrix.at(current_vertex, i) > 0)
				{
					if (auto[it, success] = result.insert(i); success)
					{
						(void)it;
						queue.push(i);
					}
				}
			}
		}

		return std::vector<msize>(result.cbegin(), result.cend());
	}

	template<class T>
	std::vector<std::vector<msize>> NonOrientedMatrixGraph<T>::get_connected_components() const
	{
		std::vector<std::vector<msize>> result;

		std::vector<bool> used(dimension());
		msize current_vertex = 0;
		while (current_vertex != dimension())
		{
			if (used[current_vertex])
			{
				current_vertex++;
				continue;
			}
			auto current_connected_component = get_connected_component(current_vertex);
			for (auto vertex : current_connected_component)
			{
				used[vertex] = true;
			}
			result.push_back(current_connected_component);
		}

		return result;
	}
    
    template<class T>
    std::list<std::vector<msize>> NonOrientedMatrixGraph<T>::get_connected_trees() const
    {
        std::vector<msize> parents(dimension(), msize_undefined);
        
        std::queue<msize> to_watch;
        for (msize i = 0; i < dimension(); to_watch.push(i++));
        
        while (!to_watch.empty())
        {
            auto vertex = to_watch.front();
            to_watch.pop();
            
            auto connected_with = msize_undefined;
            auto is_hanged = true;
            
            for (msize j = 0; j < dimension(); j++)
            {
                if (at(vertex, j) > 0 && parents[j] == msize_undefined)
                {
                    if (connected_with != msize_undefined)
                    {
                        is_hanged = false;
                        break;
                    }
                    connected_with = j;
                }
            }
            
            if (is_hanged && connected_with != msize_undefined)
            {
                parents[vertex] = connected_with;
                to_watch.emplace(connected_with);
            }
        }
        
        std::list<std::vector<msize>> result;
        std::vector<msize> trees(dimension(), msize_undefined);
        
        for (msize i = 0; i < parents.size(); i++)
        {
            if (parents[i] == msize_undefined)
            {
                bool is_tree = false;

                std::queue<msize> childs; childs.push(i);
                trees[i] = i;

                while (!childs.empty())
                {
                    auto vertex = childs.front();
                    childs.pop();
                    
                    for (msize j = 0; j < dimension(); j++)
                    {
                        if (parents[j] == vertex)
                        {
                            if (!is_tree)
                            {
                                result.emplace_back();
                                result.back().push_back(vertex);
                                is_tree = true;
                            }
                            
                            result.back().push_back(j);
                            trees[j] = i;
                            childs.push(j);
                        }
                    }
                }
            }
        }
        
        return result;
    }

	template<class InternalMatrixType>
	template<class GraphType, class MatrixType>
	GraphType NonOrientedMatrixGraph<InternalMatrixType>::with_deleted_vertexes(const std::vector<msize>& vertexes) const
	{
		return GraphType(_matrix.template with_deleted_vertexes<MatrixType>(vertexes));	
	}
		
	template<class InternalMatrixType>
	template<class GraphType, class MatrixType>
	GraphType NonOrientedMatrixGraph<InternalMatrixType>::with_deleted_edge(msize i, msize j) const
	{
		return GraphType(_matrix.template with_deleted_element<MatrixType>(i, j));
	}
}
