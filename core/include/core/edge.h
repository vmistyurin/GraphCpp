#ifndef GRAPH_CORE_EDGE_H
#define GRAPH_CORE_EDGE_H
namespace graphcpp
{
	class Edge
	{
	private:
		unsigned int _v1, _v2;

	public:
		Edge(unsigned int v1, unsigned int v2) noexcept;

		Edge(const Edge&) = delete;
		Edge operator=(const Edge&) = delete;

		bool operator==(const Edge& right) const noexcept;
		bool operator!=(const Edge& right) const noexcept;

		unsigned int v1() const noexcept;
		unsigned int v2() const noexcept;
	};
}
#endif