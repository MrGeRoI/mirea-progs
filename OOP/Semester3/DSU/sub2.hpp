#include "dsu.hpp"

namespace
{
	template <typename T>
	class sub
	{
	private:
		dsu m_dsu;
		std::vector<T> m_value;
		std::vector<int> m_end;
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
	sub<T>::sub(size_t size) : m_dsu(size), m_value(size), m_end(size)
	{
		for (int i = 0; i < size; i++)
		{
			m_end[i] = i;
		}
	}

	template <typename T>
	sub<T>::sub(const sub<T> &other) : m_dsu(other.m_dsu),
									   m_value(other.m_value),
									   m_end(other.m_end) {}

	template <typename T>
	void sub<T>::fill(int x, int y, const T &value)
	{
		if (x < 0 || x >= m_dsu.size() || y < 0 || y > m_dsu.size())
			throw std::out_of_range("");

		if (x >= y)
			return;

		for (int i = x; i < y; i++)
		{
			i = m_end[m_dsu.leader(i)];

			if (i >= y)
				break;

			m_value[i] = value;

			m_dsu.unite(x, i);
		}

		m_end[m_dsu.leader(x)] = y;
	}

	template <typename T>
	const T &sub<T>::find(int x) const
	{
		if (x < 0 || x >= m_dsu.size())
			throw std::out_of_range("");

		return m_value[x];
	}

	template <typename T>
	const std::vector<T> &sub<T>::values() const { return m_value; }

	template <typename T>
	size_t sub<T>::size() const { return m_dsu.size(); }

	template <typename T>
	void sub<T>::resize(size_t size)
	{
		if (m_dsu.size() != size)
		{
			m_dsu.resize(size);
			m_end.resize(size);
			m_value.resize(size);
		}
	}

	template <typename T>
	void sub<T>::clear()
	{
		m_dsu.clear();
		m_end.clear();
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
		m_dsu = other.m_dsu;
		m_end = other.m_end;
		m_value = other.m_value;
	}

	template <typename T>
	sub<T>::~sub() {}
}