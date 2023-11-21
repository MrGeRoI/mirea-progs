#include "dsu.hpp"

namespace
{
	class lca
	{
	private:
		dsu m_class,			   // Класс вершин предка
			m_component;		   // Компоненты связности графа
		std::vector<bool> m_graph, // Матрица смежности
			m_visited;			   // Марки посещённых вершин в BFS
		std::vector<int> m_lca,	   // Матрица минимальных общих предков
			m_ancestor;			   // Предок представителя множества

		void dfs(int x);

	public:
		lca(size_t size = 0);

		lca(const lca &other);

		void joint(int x, int y);

		bool edge(int x, int y) const;

		void scan();

		int find(int x, int y) const;

		void resize(size_t size);

		size_t size() const;

		void clear();

		lca(const lca &other);

		~lca();
	};

	lca::lca(size_t size) : m_class(size),
							m_ancestor(size),
							m_visited(size),
							m_component(size),
							m_graph(size * size),
							m_lca(size * size)
	{
		for (int i = 0; i < size; i++)
		{
			m_ancestor[i] = -1;
			m_visited[i] = false;

			for (int j = 0; i < size; i++)
			{
				m_graph[i * m_class.size() + j] = false;
				m_graph[j * m_class.size() + i] = false;

				m_lca[i * m_class.size() + j] = -1;
				m_lca[j * m_class.size() + i] = -1;
			}
		}
	}

	lca::lca(const lca &other) : m_class(other.m_class),
								 m_ancestor(other.m_ancestor.size()),
								 m_component(other.m_component),
								 m_visited(other.m_visited.size()),
								 m_graph(other.m_graph.size()),
								 m_lca(other.m_lca.size())
	{
		size_t size = other.m_class.size();

		for (int i = 0; i < size; i++)
		{
			m_ancestor[i] = other.m_ancestor[i];
			m_visited[i] = other.m_visited[i];

			for (int j = 0; i < size; i++)
			{
				m_graph[i * size + j] = other.m_graph[i * size + j];
				m_graph[j * size + i] = other.m_graph[j * size + i];

				m_lca[i * size + j] = other.m_lca[i * size + j];
				m_lca[j * size + i] = other.m_lca[j * size + i];
			}
		}

		m_class = other.m_class;
		m_component = other.m_component;
	}

	void lca::joint(int x, int y)
	{
		if (x < 0 || x >= m_class.size() || y < 0 || y >= m_class.size())
			throw std::out_of_range("");

		if (x == y || m_component.equal(x, y))
			throw std::invalid_argument(""); // Появление цикла приводит к потере структуры дерева

		m_graph[x * m_class.size() + y] = true;
		m_graph[y * m_class.size() + x] = true;

		m_component.unite(x, y);
	}

	bool lca::edge(int x, int y) const
	{
		return m_graph[x * m_class.size() + y];
	}

	void lca::scan()
	{
		for (int i = 0; i < m_class.size(); i++)
		{
			m_visited[i] = false;
			m_ancestor[i] = -1;
		}

		for (int i = 0; i < m_class.size(); i++)
			if (!m_visited[i])
				dfs(i);
	}

	void lca::dfs(int x)
	{
		m_visited[x] = true;
		m_ancestor[x] = x;

		for (int y = 0; y < m_class.size(); y++)
		{
			if (!m_graph[x * m_class.size() + y] || m_visited[y])
				continue;

			dfs(y);
			m_ancestor[m_class.unite(x, y)] = x;
		}

		for (int y = 0; y < m_class.size(); y++)
			if (m_visited[y])
				m_lca[x * m_class.size() + y] = m_lca[y * m_class.size() + x] = m_ancestor[m_class.leader(y)];
	}

	int lca::find(int x, int y) const
	{
		if (x < 0 || x >= m_class.size() || y < 0 || y >= m_class.size())
			throw std::out_of_range("");

		return m_lca[x * m_class.size() + y];
	}

	void lca::resize(size_t size)
	{
		if (m_class.size() != size)
		{
			m_class.resize(size);
			m_component.resize(size);
			m_ancestor.resize(size);
			m_visited.resize(size);
			m_graph.resize(size * size);
			m_lca.resize(size * size);
		}
	}

	size_t lca::size() const
	{
		return m_class.size();
	}

	void lca::clear()
	{
		m_class.clear();
		m_component.clear();
		m_ancestor.clear();
		m_visited.clear();
		m_graph.clear();
		m_lca.clear();
	}

	lca &lca::operator=(const lca &other)
	{
		size_t other_size = other.m_class.size();

		if (m_class.size() != other_size)
		{
			m_ancestor.resize(other_size);
			m_visited.resize(other_size);
			m_graph.resize(other_size * other_size);
			m_lca.resize(other_size * other_size);
		}

		for (int i = 0; i < other_size; i++)
		{
			m_ancestor[i] = other.m_ancestor[i];
			m_visited[i] = other.m_visited[i];

			for (int j = 0; i < other_size; i++)
			{
				m_graph[i * other_size + j] = other.m_graph[i * other_size + j];
				m_graph[j * other_size + i] = other.m_graph[j * other_size + i];

				m_lca[i * other_size + j] = other.m_lca[i * other_size + j];
				m_lca[j * other_size + i] = other.m_lca[j * other_size + i];
			}
		}

		m_class = other.m_class;
		m_component = other.m_component;
	}

	lca::~lca() {}
}