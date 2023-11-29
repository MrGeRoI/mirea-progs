#include "dsu.hpp"

namespace
{
	template <typename T>
	class sub
	{
	private:
		std::vector<T> m_value;
		std::vector<int> m_parent;

		int edge(int x)
		{
			int p = m_parent[x];

			if (p >= m_parent.size())
				return p;

			if (x == p)
				return x;

			return (m_parent[x] = edge(p));
		}

	public:
		sub(size_t size);

		sub(const sub<T> &other);

		void fill(int x, int y, const T &value);

		const T &find(int x) const;

		const std::vector<T> &values() const;

		size_t size() const;

		void resize(size_t size);

		void clear();

		const T &operator[](int x) const;

		sub &operator=(const sub<T> &other);

		~sub();
	};

	template <typename T>
	sub<T>::sub(size_t size) : m_value(size), m_parent(size)
	{
		for (int i = 0; i < size; i++)
			m_parent[i] = i;
	}

	template <typename T>
	sub<T>::sub(const sub<T> &other) : m_value(other.m_value),
									   m_parent(other.m_parent) {}

	template <typename T>
	void sub<T>::fill(int x, int y, const T &value)
	{
		if (x < 0 || x >= m_parent.size() || y < 0 || y > m_parent.size())
			throw std::out_of_range("");

		if (x >= y)
			return;

		for (int i = x; i < y; i++)
		{
			i = edge(i);

			if (i >= y)
				break;

			m_value[i] = value;
			m_parent[i] = i + 1;
		}
	}

	template <typename T>
	const T &sub<T>::find(int x) const
	{
		if (x < 0 || x >= m_parent.size())
			throw std::out_of_range("");

		return m_value[x];
	}

	template <typename T>
	const std::vector<T> &sub<T>::values() const { return m_value; }

	template <typename T>
	size_t sub<T>::size() const { return m_parent.size(); }

	template <typename T>
	void sub<T>::resize(size_t size)
	{
		if (m_parent.size() != size)
		{
			m_parent.resize(size);
			m_value.resize(size);
		}
	}

	template <typename T>
	void sub<T>::clear()
	{
		m_parent.clear();
		m_value.clear();
	}

	template <typename T>
	const T &sub<T>::operator[](int x) const
	{
		return m_value[x];
	}

	template <typename T>
	sub<T> &sub<T>::operator=(const sub<T> &other)
	{
		m_parent = other.m_parent;
		m_value = other.m_value;
	}

	template <typename T>
	sub<T>::~sub() {}
}