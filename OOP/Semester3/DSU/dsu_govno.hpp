#include <stdexcept>

namespace
{
	template <typename T = int>
	class dsu
	{
	protected:
		T *m_parent;
		int *m_rank;
		size_t *m_size, m_capacity;

	public:
		dsu(size_t size);

		dsu(const dsu<T> &other);

		T root(T x);

		T root(T x) const;

		size_t size(T x);

		size_t size(T x) const;

		void unite(T x, T y);

		bool equal(T x, T y);

		bool equal(T x, T y) const;

		T operator[](T x);

		T operator[](T x) const;

		dsu<T> &operator=(const dsu<T> &other);

		~dsu();
	};

	template <typename T>
	dsu<T>::dsu(size_t capacity) : m_capacity(capacity),
								   m_parent(new T[capacity]),
								   m_rank(new int[capacity]),
								   m_size(new size_t[capacity])
	{
		for (T i = 0; i < capacity; i++)
		{
			m_parent[i] = i; // Родитель
			m_rank[i] = 0;	 // Ранг
			m_size[i] = 1;	 // Размер
		}
	}

	template <typename T>
	dsu<T>::dsu(const dsu<T> &other) : m_capacity(other.m_capacity),
									   m_parent(new T[other.m_capacity]),
									   m_rank(new int[other.m_capacity]),
									   m_size(new size_t[other.m_capacity])
	{
		for (T i = 0; i < m_capacity; i++)
		{
			m_parent[i] = other.m_parent[i];
			m_rank[i] = other.m_rank[i];
			m_size[i] = other.m_size[i];
		}
	}

	template <typename T>
	T dsu<T>::root(T x)
	{
		if (x < 0 || x >= m_capacity)
			throw std::out_of_range("");

		T p = m_parent[x];

		if (x == p)
			return x;

		return (m_parent[x] = root(p));
	}

	template <typename T>
	T dsu<T>::root(T x) const
	{
		if (x < 0 || x >= m_capacity)
			throw std::out_of_range("");

		T p = m_parent[x];

		if (x == p)
			return x;

		return root(p);
	}

	template <typename T>
	size_t dsu<T>::size(T x)
	{
		if (x < 0 || x >= m_capacity)
			throw std::out_of_range("");

		return m_size[root(x)];
	}

	template <typename T>
	size_t dsu<T>::size(T x) const
	{
		if (x < 0 || x >= m_capacity)
			throw std::out_of_range("");

		return m_size[root(x)];
	}

	template <typename T>
	void dsu<T>::unite(T x, T y)
	{
		if (x < 0 || x >= m_capacity || y < 0 || y >= m_capacity)
			throw std::out_of_range("");

		x = root(x);
		y = root(y);

		if (x == y)
			return;

		if (m_rank[x] < m_rank[y])
			std::swap(x, y);

		m_size[x] += m_size[y];

		m_parent[y] = x;

		if (m_rank[x] == m_rank[y])
			m_rank[x]++;
	}

	template <typename T>
	bool dsu<T>::equal(T x, T y)
	{
		if (x < 0 || x >= m_capacity || y < 0 || y >= m_capacity)
			throw std::out_of_range("");

		return root(x) == root(y);
	}

	template <typename T>
	bool dsu<T>::equal(T x, T y) const
	{
		if (x < 0 || x >= m_capacity || y < 0 || y >= m_capacity)
			throw std::out_of_range("");

		return root(x) == root(y);
	}

	template <typename T>
	T dsu<T>::operator[](T x)
	{
		return root(x);
	}

	template <typename T>
	T dsu<T>::operator[](T x) const
	{
		return root(x);
	}

	template <typename T>
	dsu<T> &dsu<T>::operator=(const dsu<T> &other)
	{
		if (m_capacity != other.m_capacity)
		{
			m_capacity = other.m_capacity;

			delete[] m_parent;
			delete[] m_rank;
			delete[] m_size;

			m_parent = new T[m_capacity];
			m_rank = new int[m_capacity];
			m_size = new size_t[m_capacity];
		}

		for (int i = 0; i < m_capacity; i++)
		{
			m_parent[i] = other.m_parent[i];
			m_rank[i] = other.m_rank[i];
			m_size[i] = other.m_size[i];
		}

		return *this;
	}

	template <typename T>
	dsu<T>::~dsu()
	{
		delete[] m_parent;
		delete[] m_rank;
		delete[] m_size;
	}
}