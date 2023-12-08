#include "unordered_dsu.hpp"

namespace
{
	class graph
	{
	private:
		unordered_dsu m_components;
		std::vector<bool> m_parity, m_bipartite;

	public:
		graph(size_t size) : m_components(size),
							 m_parity(size, 0),
							 m_bipartite(size, true) {}

		graph(const graph &other) : m_components(other.m_components),
									m_parity(other.m_parity),
									m_bipartite(other.m_bipartite) {}

		void joint(int x, int y)
		{
		}

		bool edge(int x, int y) const
		{
		}

		bool bipartite(int v)
		{
			return m_bipartite[find_set(v).first];
		}

		graph &operator=(const graph &other)
		{
			m_components = other.m_components;
			m_parity = other.m_parity;
			m_bipartite = other.m_bipartite;
		}

		~graph() {}
	};
}