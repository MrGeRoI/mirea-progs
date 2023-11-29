#include <stdexcept>
#include <vector>

namespace
{
	class dsu
	{
	protected:
		std::vector<int> m_rank,	 // Ранги вершин
			m_parent;				 // Родители вершин
		std::vector<size_t> m_count; // Мощность множества

	public:
		dsu(size_t size = 0);

		dsu(const dsu &other);

		int leader(int x);

		int leader(int x) const;

		size_t count(int x);

		size_t count(int x) const;

		inline size_t size() const;

		void resize(size_t size);

		int unite(int x, int y);

		bool equal(int x, int y);

		bool equal(int x, int y) const;

		void clear();

		int operator[](int x);

		int operator[](int x) const;

		dsu &operator=(const dsu &other);

		~dsu();
	};

	dsu::dsu(size_t size) : m_parent(size),
							m_rank(size),
							m_count(size)
	{
		for (int i = 0; i < size; i++)
		{
			m_parent[i] = i;
			m_rank[i] = 0;
			m_count[i] = 1;
		}
	}

	dsu::dsu(const dsu &other) : m_parent(other.m_parent),
								 m_rank(other.m_parent),
								 m_count(other.m_count) {}

	int dsu::leader(int x)
	{
		if (x < 0 || x >= m_parent.size())
			throw std::out_of_range("");

		int p = m_parent[x];

		if (x == p)
			return x;

		return (m_parent[x] = leader(p));
	}

	int dsu::leader(int x) const
	{
		if (x < 0 || x >= m_parent.size())
			throw std::out_of_range("");

		int p = m_parent[x];

		if (x == p)
			return x;

		return leader(p);
	}

	size_t dsu::count(int x)
	{
		if (x < 0 || x >= m_parent.size())
			throw std::out_of_range("");

		return m_count[leader(x)];
	}

	size_t dsu::count(int x) const
	{
		if (x < 0 || x >= m_parent.size())
			throw std::out_of_range("");

		return m_count[leader(x)];
	}

	size_t dsu::size() const
	{
		return m_parent.size();
	}

	void dsu::resize(size_t size)
	{
		if (m_parent.size() != size)
		{
			m_parent.resize(size);
			m_rank.resize(size);
			m_count.resize(size);
		}
	}

	int dsu::unite(int x, int y)
	{
		if (x < 0 || x >= m_parent.size() || y < 0 || y >= m_parent.size())
			throw std::out_of_range("");

		x = leader(x);
		y = leader(y);

		if (x == y)
			return x;

		if (m_rank[x] < m_rank[y])
			std::swap(x, y);

		m_count[x] += m_count[y];

		m_parent[y] = x;

		if (m_rank[x] == m_rank[y])
			m_rank[x]++;

		return x;
	}

	bool dsu::equal(int x, int y)
	{
		if (x < 0 || x >= m_parent.size() || y < 0 || y >= m_parent.size())
			throw std::out_of_range("");

		return leader(x) == leader(y);
	}

	bool dsu::equal(int x, int y) const
	{
		if (x < 0 || x >= m_parent.size() || y < 0 || y >= m_parent.size())
			throw std::out_of_range("");

		return leader(x) == leader(y);
	}

	void dsu::clear()
	{
		m_parent.clear();
		m_rank.clear();
		m_count.clear();
	}

	int dsu::operator[](int x)
	{
		return leader(x);
	}

	int dsu::operator[](int x) const
	{
		return leader(x);
	}

	dsu &dsu::operator=(const dsu &other)
	{
		m_parent = other.m_parent;
		m_rank = other.m_rank;
		m_count = other.m_count;

		return *this;
	}

	dsu::~dsu() {}

}