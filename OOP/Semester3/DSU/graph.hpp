#include "unordered_dsu.hpp"

namespace
{
	class graph
	{
	private:
		unordered_dsu m_components;
		std::vector<bool> m_parity, m_bipartite;

	public:
		graph(size_t size) : m_components(size), m_parity(size), m_bipartite(size)
		{
			for(int i = 0;i < size;i++)
			{
				m_bipartite[i] = true;
			}
		}

		void joint(int x, int y)
		{
		}

		bool edge(int x, int y) const
		{
		}

		bool bipartite(int v)
		{
			return bipartite[find_set(v).first];
		}
	};
}